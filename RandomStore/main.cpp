#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include "naiverandomstore.h"
#include "randomstore.h"

template <typename Func>
auto timeFunc(Func func, const std::string &name) -> double {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << name << ": " << elapsed_seconds.count() << "s\n";
    return elapsed_seconds.count();
}

auto main() -> int {
    RandomStore<int> store;
    NaiveRandomStore<int> naive_store;

    // insert 1000 items
    // 1. naive store

    double naive = timeFunc(
        [&]() {
            for (int i = 0; i < 1000; i++) {
                naive_store.insert(i);
            }
        },
        "naive insert");

    // 2. random store
    double optimized = timeFunc(
        [&]() {
            for (int i = 0; i < 1000; i++) {
                store.insert(i);
            }
        },
        "random insert");

    std::cout << "optimized / naive: " << optimized / naive << "\n";
    std::cout << "naive / optimized: " << naive / optimized << "\n";

    // remove 100 items
    // 1. naive store
    naive = timeFunc(
        [&]() {
            for (int i = 0; i < 100; i++) {
                naive_store.remove(i);
            }
        },
        "naive remove");

    // 2. random store
    optimized = timeFunc(
        [&]() {
            for (int i = 0; i < 100; i++) {
                store.remove(i);
            }
        },
        "random remove");

    std::cout << "optimized / naive: " << optimized / naive << "\n";
    std::cout << "naive / optimized: " << naive / optimized << "\n";

    // select random 1000 times
    // 1. naive store
    naive = timeFunc(
        [&]() {
            for (int i = 0; i < 1000; i++) {
                naive_store.selectRandom();
            }
        },
        "naive select random");

    // 2. random store
    optimized = timeFunc(
        [&]() {
            for (int i = 0; i < 1000; i++) {
                store.selectRandom();
            }
        },
        "random select random");

    std::cout << "optimized / naive: " << optimized / naive << "\n";
    std::cout << "naive / optimized: " << naive / optimized << "\n";

    return 0;
}
