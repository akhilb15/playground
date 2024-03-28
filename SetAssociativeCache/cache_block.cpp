/*
    @file cache_block.cpp
    @brief Implementation of CacheBlock class
*/

#include "cache_block.h"

Cache::Block::Block(int block_size) : block_size_(block_size) {
    data_.resize(block_size);
}