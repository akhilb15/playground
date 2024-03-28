/**
 * @file mutex.h
 * @author Akhil Bharanidhar
 * @brief 
 * @version 0.1
 * @date 2024-03-26
 * 
 */


#ifndef __MUTEX_H__
#define __MUTEX_H__

#include <atomic>
#include <thread>

#define UNASSIGNED std::thread::id()

#define LOCKED true
#define UNLOCKED false

class Mutex {
    public:
        /**
         * @brief Construct a new Mutex object
         * 
         */
        Mutex() : locked(UNLOCKED) {
            owner = UNASSIGNED;
        }

        Mutex(const Mutex&) = delete;
        Mutex& operator=(const Mutex&) = delete;

        /**
         * @brief Acquire the mutex
         * 
         */
        void acquire();

        /**
         * @brief Release the mutex
         * 
         */
        void release();

    private:
        std::atomic_flag locked;
        std::thread::id owner;
};


#endif /* __MUTEX_H__ */