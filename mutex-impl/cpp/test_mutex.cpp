/**
 * @file test_mutex.cpp
 * @author Akhil Bharanidhar
 * @brief test mutex impl
 * @version 0.1
 * @date 2024-03-26
 * 
 */

#include "mutex.h"

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <unistd.h>

#define NUM_THREADS 10

Mutex m;
std::mutex stdm;
int counter = 0;

void increment(int thread_idx) {
    for (int i = 0; i < 100; i++) {
        m.acquire();
        // stdm.lock();

        // sleep(1);
        counter++;
        std::cout << "Thread " << thread_idx << " incremented counter to " << counter << std::endl;

        m.release();
        // stdm.unlock();
    }
}

int main() {
    std::vector<std::thread> threads(NUM_THREADS);
    // time execution
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i] = std::thread(increment, i);
    }

    for (auto& t : threads) {
        t.join();
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Elapsed time: " << elapsed.count() << "s" << std::endl;
    std::cout << "Counter: " << counter << std::endl;
    return 0;
}
