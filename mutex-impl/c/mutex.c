/**
 * @file mutex.c
 * @author Akhil Bharanidhar
 * @brief 
 * @version 0.1
 * @date 2024-03-25
 * 
 */


#include "mutex.h"

/* Compiler directives to hint that the expression is likely to be true (likely)/false (unlikely) */
#define likely(expr) __builtin_expect(!!(expr), 1)
#define unlikely(expr) __builtin_expect(!!(expr), 0)


int mutex_init(mutex_t *m) {
    if (m == NULL) {
        return -1;
    }
    // atomic_flag_clear_explicit(&m->locked, memory_order_release);
    atomic_flag_clear(&m->locked);
    m->owner = UNASSIGNED;
    return 0;
}

int mutex_acquire(mutex_t *m) {
    if (m == NULL) {
        return -1;
    }
    /*`
    * atomic_flag_test_and_set` orders memory accesses according 
    * to `memory_order_seq_cst` (sequentially consistent).
    * - https://gcc.gnu.org/wiki/Atomic/GCCMM/AtomicSync
    * - acquire/release is faster but sometimes won't work as you expect
    */
    // while (atomic_flag_test_and_set_explicit(&m->locked, memory_order_acquire)) { 
    while (atomic_flag_test_and_set(&m->locked)) { // returns true if the flag was already set
        sched_yield(); // yield the processor
    }
    m->owner = pthread_self();
    return 0;
}

int mutex_release(mutex_t *m) {
    if (m == NULL) {
        return -1;
    }
    if (unlikely(m->owner != pthread_self())) {
        return -1;
    }
    // atomic_flag_clear_explicit(&m->locked, memory_order_release);
    atomic_flag_clear(&m->locked);
    m->owner = UNASSIGNED;
    return 0;
}
