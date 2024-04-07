/**
 * @file mutex.h
 * @author Akhil Bharanidhar
 * @brief Implementation of Mutex using atomics
 * @version 0.1
 * @date 2024-03-25
 * 
 */

#ifndef __MUTEX_H__
#define __MUTEX_H__


#include <stdatomic.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <linux/futex.h>
#include <unistd.h>


#define UNASSIGNED 0

#define MUTEX_INITIALIZER {ATOMIC_FLAG_INIT, UNASSIGNED}


typedef struct __mutex_t {
    atomic_flag locked;
    pthread_t owner;
} mutex_t;

/**
 * @brief Initialize the mutex
 * 
 * @param m 
 */
int mutex_init(mutex_t *m);

/**
 * @brief Lock the mutex
 * 
 * @param m 
 */
int mutex_acquire(mutex_t *m);

/**
 * @brief Unlock the mutex
 * 
 * @param m 
 */
int mutex_release(mutex_t *m);


/**
 * @brief wrapper for the futex system call
 * 
 * @param uaddr - pointer to the futex
 * @param futex_op - operation to be performed
 * @param val - value to be compared
 * @param timeout - timeout value
 * @param uaddr2 - pointer to the second futex
 * @param val3 - value to be compared with the second futex
 *
 * @return int - return value of the futex system call
 */
static int futex(uint32_t *uaddr, int futex_op, uint32_t val, const struct timespec *timeout, uint32_t *uaddr2, uint32_t val3) {
    return syscall(SYS_futex, uaddr, futex_op, val, timeout, uaddr2, val3);
}


#endif /* __MUTEX_H__ */
