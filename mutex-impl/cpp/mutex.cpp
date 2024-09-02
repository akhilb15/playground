/**
 * @file mutex.cpp
 * @author Akhil Bharanidhar
 * @brief implementation of mutex
 * @version 0.1
 * @date 2024-03-26
 * 
 */

#include "mutex.h"

/* Compiler directives to hint that the expression is likely to be true (likely)/false (unlikely) */
#define likely(expr) __builtin_expect(!!(expr), 1)
#define unlikely(expr) __builtin_expect(!!(expr), 0)

void Mutex::acquire() {
    //while (locked.test_and_set(std::memory_order_acquire)) {
    while (locked.test_and_set()) { // uses std::memory_order_seq_cst by default
        std::this_thread::yield();
        // locked.wait(LOCKED);
    }
    owner = std::this_thread::get_id();
}

void Mutex::release() {
    if (unlikely(owner != std::this_thread::get_id())) {
        throw std::runtime_error("Mutex not owned by calling thread");
    }
    owner = UNASSIGNED;
    //locked.clear(std::memory_order_release);
    locked.clear();
    // locked.notify_one(); // wake up a waiting thread
}
