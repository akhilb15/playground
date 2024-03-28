

class CacheBlock:
    def __init__(self, tag, data, valid=True):
        self.tag = tag
        self.data = data
        self.valid = valid

class DirectMappedCache:
    def __init__(self, size, block_size):
        assert(size % block_size == 0)

        self.size = size
        self.block_size = block_size
        self.num_sets = size // block_size
        
        self.cache = [CacheBlock(0xff, [0xff] * block_size, False) for i in range(self.num_sets)]
        self.hits = 0
        self.misses = 0

    def read(self, address):
        offset = address % self.block_size
        index = (address // self.block_size) % self.num_sets
        tag = address // (self.block_size * self.num_sets)

        if self.cache[index].valid and self.cache[index].tag == tag:
            self.hits += 1
            print("READ {} : HIT".format(hex(address)))
            return self.cache[index].data[offset]
        else:
            self.misses += 1
            self.cache[index].tag = tag
            self.cache[index].valid = True
            
            block_addr = address - offset
            self.cache[index].data = [block_addr + i for i in range(self.block_size)]

            print("READ {} : MISS".format(hex(address)))
            return self.cache[index].data[offset]
 
    def __str__(self):
        output = "Direct Mapped Cache: Size = {}, Block Size = {}\n".format(self.size, self.block_size)
        # print cache contents as a table
        output += "Index\tValid\tTag\tData\n"
        for i in range(self.num_sets):
            output += "{}\t{}\t{}\t{}\n".format(i, self.cache[i].valid, hex(self.cache[i].tag), [hex(x) for x in self.cache[i].data])
        output += "\nHits: " + str(self.hits) + "\n"
        output += "Misses: " + str(self.misses) + "\n"
        
        return output

#
# accesses = [0x4, 0xb, 0x0, 0xa, 0xd, 0x8]
#
# cache = DirectMappedCache(8, 2)
#
# for access in accesses:
#     print("Read {} from {}\n".format(cache.read(access), hex(access)))
#
# print(cache)
#

def get_cache_location(address, cache_size, block_size, associativity):
    offset = address % block_size
    num_sets = cache_size // (block_size * associativity)

    index = (address // block_size) % num_sets

    tag = address // (block_size * num_sets)

    return (offset, index, tag)


def print_cache_location(address, cache_size, block_size, associativity):
    print("Offset: {}\nIndex: {}\nTag: {}".format(*get_cache_location(address, cache_size, block_size, associativity)))

CACHE_SIZE = 512
BLOCK_SIZE = 16
ASSOCIATIVITY = 2

address = 0x575700

print_cache_location(address, CACHE_SIZE, BLOCK_SIZE, ASSOCIATIVITY)

address = 0x31D100

print_cache_location(address, CACHE_SIZE, BLOCK_SIZE, ASSOCIATIVITY)




