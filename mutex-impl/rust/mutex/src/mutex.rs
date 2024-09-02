/// basic mutex implementation in rust
use std::cell::UnsafeCell;
use std::hint::spin_loop;
use std::ops::Deref;
use std::ops::DerefMut;
use std::sync::atomic::{AtomicU8, Ordering};

#[derive(Debug)]
pub enum MutexError {
    Poisoned,
    WouldBlock,
}

enum MutexState {
    Unlocked = 0,
    Locked = 1,
    Poisoned = 2,
}

pub struct Mutex<T> {
    data: UnsafeCell<T>,
    state: AtomicU8,
}

pub struct LockGuard<'a, T> {
    mutex: &'a Mutex<T>,
}

unsafe impl<T> Sync for Mutex<T> {}
unsafe impl<T> Send for Mutex<T> {}

impl<T> Mutex<T> {
    pub fn new(data: T) -> Mutex<T> {
        Mutex {
            data: UnsafeCell::new(data),
            state: AtomicU8::new(MutexState::Unlocked as u8),
        }
    }

    pub fn lock(&self) -> Result<LockGuard<T>, MutexError> {
        loop {
            match self.state.compare_exchange(
                MutexState::Unlocked as u8,
                MutexState::Locked as u8,
                Ordering::Acquire,
                Ordering::Relaxed,
            ) {
                Ok(_) => return Ok(LockGuard { mutex: self }),
                Err(state) => {
                    if state == MutexState::Poisoned as u8 {
                        return Err(MutexError::Poisoned);
                    }
                    spin_loop();
                }
            }
        }
    }

    pub fn try_lock(&self) -> Result<LockGuard<T>, MutexError> {
        match self.state.compare_exchange(
            MutexState::Unlocked as u8,
            MutexState::Locked as u8,
            Ordering::Acquire,
            Ordering::Relaxed,
        ) {
            Ok(_) => Ok(LockGuard { mutex: self }),
            Err(state) => {
                if state == MutexState::Poisoned as u8 {
                    Err(MutexError::Poisoned)
                } else {
                    Err(MutexError::WouldBlock)
                }
            }
        }
    }

    /// drop the lock guard to unlock the mutex
    /// it's empty! we take ownership of the lock guard and drop it
    pub fn unlock(&self, _guard: LockGuard<T>) {}
}

impl<'a, T> Deref for LockGuard<'a, T> {
    type Target = T;

    fn deref(&self) -> &T {
        unsafe { &*self.mutex.data.get() }
    }
}

impl<'a, T> DerefMut for LockGuard<'a, T> {
    fn deref_mut(&mut self) -> &mut T {
        unsafe { &mut *self.mutex.data.get() }
    }
}

impl<'a, T> Drop for LockGuard<'a, T> {
    fn drop(&mut self) {
        if std::thread::panicking() {
            self.mutex
                .state
                .store(MutexState::Poisoned as u8, Ordering::Relaxed);
        } else {
            self.mutex
                .state
                .store(MutexState::Unlocked as u8, Ordering::Release);
        }
    }
}

// #[derive(Debug)]
// pub enum MutexError {
//     Poisoned,
// }

// pub struct Mutex<T> {
//     data: UnsafeCell<T>,
//     lock: AtomicBool,
//     poisoned: AtomicBool,
// }

// pub struct LockGuard<'a, T> {
//     mutex: &'a Mutex<T>,
// }

// unsafe impl<T> Sync for Mutex<T> {}
// unsafe impl<T> Send for Mutex<T> {}

// impl<T> Mutex<T> {
//     pub fn new(data: T) -> Mutex<T> {
//         Mutex {
//             data: UnsafeCell::new(data),
//             lock: AtomicBool::new(false),
//             poisoned: AtomicBool::new(false),
//         }
//     }

//     pub fn lock(&self) -> Result<LockGuard<T>, MutexError> {
//         while self.lock.swap(true, Ordering::Acquire) {
//             spin_loop();
//         }

//         // if mutex is poisoned, set the lock to false and return an error
//         // we set the lock to false to stop other threads from waiting on the mutex
//         // otherwise, return the lock guard
//         if self.poisoned.load(Ordering::Relaxed) {
//             self.lock.store(false, Ordering::Release);
//             Err(MutexError::Poisoned)
//         } else {
//             Ok(LockGuard { mutex: self })
//         }
//     }

//     /// drop the lock guard to unlock the mutex
//     /// it's empty! we take ownership of the lock guard and drop it
//     pub fn unlock(&self, _guard: LockGuard<T>) {}
// }

// impl<'a, T> Deref for LockGuard<'a, T> {
//     type Target = T;

//     fn deref(&self) -> &T {
//         unsafe { &*self.mutex.data.get() }
//     }
// }

// impl<'a, T> DerefMut for LockGuard<'a, T> {
//     fn deref_mut(&mut self) -> &mut T {
//         unsafe { &mut *self.mutex.data.get() }
//     }
// }

// impl<'a, T> Drop for LockGuard<'a, T> {
//     fn drop(&mut self) {
//         // if panic occurs, set mutex status to poisoned
//         if std::thread::panicking() {
//             self.mutex.poisoned.store(true, Ordering::Relaxed);
//         }
//         // even if panic, unlock mutex to stop other threads from blocking
//         self.mutex.lock.store(false, Ordering::Release);
//     }
// }
