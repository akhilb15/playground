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


#endif /* __MUTEX_H__ */
