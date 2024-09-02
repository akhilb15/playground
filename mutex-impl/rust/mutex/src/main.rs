use std::sync::{Arc, Mutex as StdMutex};

mod mutex;
use mutex::Mutex;

// test mutex implementation by having threads increment a shared counter
fn test_mutex(num_threads: usize) {
    let counter = Arc::new(Mutex::new(0));

    let mut handles = vec![];
    for i in 0..num_threads {
        let counter: Arc<Mutex<usize>> = Arc::clone(&counter);
        let handle = std::thread::spawn(move || {
            for _ in 0..1000 {
                let mut num = counter.lock().unwrap();
                *num += 1;
                println!("thread {}: counter: {}", i, *num);
            }
        });
        handles.push(handle);
    }

    for handle in handles {
        handle.join().unwrap();
    }

    let num = counter.lock().unwrap();

    println!("FINAL -- counter: {}", *num);

    assert_eq!(*num, num_threads * 1000);
}

fn main() {
    test_mutex(10);
}
