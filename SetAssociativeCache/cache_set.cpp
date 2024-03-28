/*
    @file cache_set.cpp
    @brief Implementation of CacheSet class
*/

#include "cache_set.h"

Cache::Set::Set(int associativity, int block_size)
    : associativity_(associativity),
      block_size_(block_size),
      plru_(associativity) {
    blocks_.resize(associativity);
    for (int i = 0; i < associativity; i++) {
        blocks_[i] = std::make_shared<Block>(block_size);
    }
}

int Cache::Set::associativity() const { return associativity_; }

int Cache::Set::block_size() const { return block_size_; }

std::shared_ptr<Cache::Block> Cache::Set::GetBlock(int tag) {
    if (tag_to_index_.find(tag) == tag_to_index_.end()) {
        // block not found
        return nullptr;
    }
    int index = tag_to_index_[tag];
    plru_.update(index);
    return blocks_[index];
}
