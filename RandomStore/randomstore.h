
#pragma once

#include <map>
#include <vector>

template <typename T>
class RandomStore {
   public:
    void insert(const T &item);
    void remove(const T &item);
    auto selectRandom() -> T;

   private:
    std::vector<T> items;
    std::map<T, size_t> items_map;
    size_t first_valid_idx = 0;
};

template <typename T>
void RandomStore<T>::insert(const T &item) {
    if (items_map.contains(item)) {
        return;
    }
    items.push_back(item);
    items_map[item] = items.size() - 1;
}

template <typename T>
void RandomStore<T>::remove(const T &item) {
    if (!items_map.contains(item)) {
        return;
    }
    size_t idx = items_map[item];

    // swap with element at first valid index
    std::swap(items[idx], items[first_valid_idx]);

    // update map
    items_map[items[idx]] = idx;
    items_map.erase(item);

    // update starting idx
    first_valid_idx++;
}

template <typename T>
auto RandomStore<T>::selectRandom() -> T {
    if (first_valid_idx == items.size()) {
        return T();
    }
    // choose random index
    size_t idx = first_valid_idx + rand() % (items.size() - first_valid_idx);
    return items[idx];
}
