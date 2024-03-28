#ifndef __CACHE_BLOCK_H__
#define __CACHE_BLOCK_H__

#include <cstdint>
#include <memory>
#include <vector>

#include "cache.h"

class Cache::Block {
   public:
    explicit Block(int block_size);

    bool dirty() const;
    void set_dirty(bool dirty);

    bool valid() const;
    void set_valid(bool valid);

    int tag() const;
    void set_tag(int tag);

    int block_size() const;

    std::vector<std::uint8_t> data() const;
    void SetData(std::vector<std::uint8_t> data);

    void ReadFromMemory(std::shared_ptr<Memory> memory, int address);
    void WriteToMemory(std::shared_ptr<Memory> memory, int address);

   private:
    bool dirty_ = false;
    bool valid_ = false;
    int tag_ = 0;
    int block_size_ = 0;
    std::vector<std::uint8_t> data_;
};

#endif  // __CACHE_BLOCK_H__