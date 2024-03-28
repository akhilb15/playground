#ifndef __CACHE_H__
#define __CACHE_H__

#include <map>
#include <memory>
#include <vector>

#include "memory.h"

class Cache {
   public:
    class Set;
    class Block;

    explicit Cache(int size, int associativity, int block_size);

    int associativity() const;
    int block_size() const;

   private:
};

#endif  // __CACHE_H__
