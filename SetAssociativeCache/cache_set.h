#ifndef __SET_H__
#define __SET_H__

#include <memory>
#include <vector>

#include "cache.h"

// A set is a collection of cache blocks.
// should use PLRU to determine which block to evict
// PLRU implementation:

class Cache::Set {
   public:
    explicit Set(int associativity, int block_size);

    int associativity() const;
    int block_size() const;

    std::shared_ptr<Block> GetBlock(int tag);
    std::shared_ptr<Block> GetLRUBlock();

   private:
    class PLRU {
       public:
        explicit PLRU(int associativity) {
            associativity_ = associativity;
            tree_.resize(2 * associativity - 1);
        }
        int getLRU() {}
        void update(int index);

       private:
        int associativity_;
        std::vector<int> tree_;
    };

    int associativity_ = 0;
    int block_size_ = 0;
    std::vector<std::shared_ptr<Block>> blocks_;
    PLRU plru_;
    std::map<int, int> tag_to_index_;
};

#endif  // __SET_H__