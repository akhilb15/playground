

class CacheBlock:
    def __init__(self, tag, data, valid=True):
        self.tag = tag
        self.data = data
        self.valid = valid
#
# class DirectMappedCache:
#     def __init__(self, size, block_size):
#         assert(size % block_size == 0)
#
#         self.size = size
#         self.block_size = block_size
#         self.num_sets = size // block_size
#         
#         self.cache = [CacheBlock(0xff, [0xff] * block_size, False) for i in range(self.num_sets)]
#         self.hits = 0
#         self.misses = 0
#
#     def read(self, address):
#         offset = address % self.block_size
#         index = (address // self.block_size) % self.num_sets
#         tag = address // (self.block_size * self.num_sets)
#
#         if self.cache[index].valid and self.cache[index].tag == tag:
#             self.hits += 1
#             print("READ {} : HIT".format(hex(address)))
#             return self.cache[index].data[offset]
#         else:
#             self.misses += 1
#             self.cache[index].tag = tag
#             self.cache[index].valid = True
#             
#             block_addr = address - offset
#             self.cache[index].data = [block_addr + i for i in range(self.block_size)]
#
#             print("READ {} : MISS".format(hex(address)))
#             return self.cache[index].data[offset]
#  
#     def __str__(self):
#         output = "Direct Mapped Cache: Size = {}, Block Size = {}\n".format(self.size, self.block_size)
#         # print cache contents as a table
#         output += "Index\tValid\tTag\tData\n"
#         for i in range(self.num_sets):
#             output += "{}\t{}\t{}\t{}\n".format(i, self.cache[i].valid, hex(self.cache[i].tag), [hex(x) for x in self.cache[i].data])
#         output += "\nHits: " + str(self.hits) + "\n"
#         output += "Misses: " + str(self.misses) + "\n"
#         
#         return output


class SetAssociativeCache:
    # each set is lru cache
    def __init__(self, size, block_size, associativity):
        assert(size % (block_size * associativity) == 0)
        self.size = size
        self.block_size = block_size
        self.associativity = associativity
        self.num_sets = size // (block_size * associativity)
        
        self.cache = [[CacheBlock(0xff, [0xff] * block_size, False) for i in range(associativity)] for j in range(self.num_sets)]
        self.hits = 0
        self.misses = 0

        # create lru list for each set
        self.lru = [[i for i in range(associativity)] for j in range(self.num_sets)]

    def read(self, address):
        offset = address % self.block_size
        index = (address // self.block_size) % self.num_sets
        tag = address // (self.block_size * self.num_sets)
        
        for i in range(self.associativity):
            if self.cache[index][i].valid and self.cache[index][i].tag == tag:
                self.hits += 1
                print("READ {} : HIT".format(hex(address)))
                # update lru list
                self.lru[index].remove(i)
                self.lru[index].append(i)
                
                for k, lru_list in enumerate(self.lru):
                    print("Set {} LRU: {}".format(k, lru_list))

                return self.cache[index][i].data[offset]
        
        self.misses += 1
        # print type of miss
        
        # capacity miss - if the entire cache is full
        if all([block.valid for cache_set in self.cache for block in cache_set]):
            print("READ {} : CAPACITY MISS".format(hex(address)))
        # conflict miss - cache set is full       
        elif all([block.valid for block in self.cache[index]]):
            print("READ {} : CONFLICT MISS".format(hex(address)))
        # compulsory/cold miss - first time access
        else:
            print("READ {} : COMPULSORY MISS".format(hex(address)))

        lru_block = self.lru[index].pop(0)
        
        self.cache[index][lru_block].tag = tag
        self.cache[index][lru_block].valid = True

        block_addr = address - offset
        self.cache[index][lru_block].data = [block_addr + i for i in range(self.block_size)]

        # update lru list
        self.lru[index].append(lru_block)

        for i, lru_list in enumerate(self.lru):
            print("Set {} LRU: {}".format(i, lru_list))

        return self.cache[index][lru_block].data[offset]

    def __str__(self):
        output = "Set Associative Cache: Size = {}, Block Size = {}, Associativity = {}\n".format(self.size, self.block_size, self.associativity)

        output += "".join([f"Way {i}\t" for i in range(self.associativity)])[:-1] + "\n"
        for i in range(self.num_sets):
            output += "".join([f"{hex(self.cache[i][j].tag) if self.cache[i][j].valid else 'EMPTY'}\t" for j in range(self.associativity)])[:-1] + "\n"
            
        output += "\nHits: " + str(self.hits) + "\n"
        output += "Misses: " + str(self.misses) + "\n"

        return output

    #
    # def __str__(self):
    #     output = "Set Associative Cache: Size = {}, Block Size = {}, Associativity = {}\n".format(self.size, self.block_size, self.associativity)
    #     # print cache contents as a table
    #     output += "Index\tWay\tValid\tTag\tData\n"
    #     for i in range(self.num_sets):
    #         for j in range(self.associativity):
    #             output += "{}\t{}\t{}\t{}\t{}\n".format(i, j, self.cache[i][j].valid, hex(self.cache[i][j].tag), [hex(x) for x in self.cache[i][j].data])
    #     output += "\nHits: " + str(self.hits) + "\n"
    #     output += "Misses: " + str(self.misses) + "\n"
    #     
    #     return output
    #


def get_cache_location(address, cache_size, block_size, associativity):
    offset = address % block_size
    num_sets = cache_size // (block_size * associativity)
    index = (address // block_size) % num_sets
    tag = address // (block_size * num_sets)
    return (offset, index, tag)


def print_cache_location(address, cache_size, block_size, associativity):
    print("Offset: {}\nIndex: {}\nTag: 0x{:x}".format(*get_cache_location(address, cache_size, block_size, associativity)))


CACHE_SIZE = 128
BLOCK_SIZE = 16
ASSOCIATIVITY = 4

if __name__ == "__main__":
    cache = SetAssociativeCache(CACHE_SIZE, BLOCK_SIZE, ASSOCIATIVITY)

    addresses = [0x103, 0x383, 0x3f0, 0x2ae, 0x203, 0x02b, 0x000, 0x123, 0x208, 0x300, 0x02b, 0x103]

    print(cache)

    for addr in addresses:
        print_cache_location(addr, CACHE_SIZE, BLOCK_SIZE, ASSOCIATIVITY)
        print('')
        cache.read(addr)
        print('')
        print(cache)
        print('')
        breakpoint()
        
        # print_cache_location(addr, CACHE_SIZE, BLOCK_SIZE, ASSOCIATIVITY)
        # print('') 

    print(cache)



