
#pragma once

#include <set>

template <typename T>
class NaiveRandomStore {
   public:
    void insert(const T &item);
    void remove(const T &item);
    auto selectRandom() -> T;

   private:
    std::set<T> items;
};

template <typename T>
void NaiveRandomStore<T>::insert(const T &item) {
    items.insert(item);
}

template <typename T>
void NaiveRandomStore<T>::remove(const T &item) {
    items.erase(item);
}

template <typename T>
auto NaiveRandomStore<T>::selectRandom() -> T {
    if (items.empty()) {
        return T();
    }
    auto it = items.begin();
    std::advance(it, rand() % items.size());
    return *it;
}