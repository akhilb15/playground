/*
    @file memory.cpp
    @brief Implementation of Memory class
*/

#include "memory.h"

Memory::Memory(std::uint32_t size) : size_(size) {
    data_.resize(size);
    // initalize all memory to random bytes
    for (int i = 0; i < size_; i++) {
        data_[i] = rand() % 256;
    }
}

std::uint8_t Memory::ReadByte(int address) const { return data_[address]; }

void Memory::WriteByte(int address, std::uint8_t value) {
    data_[address] = value;
}

std::vector<std::uint8_t> Memory::ReadBlock(std::uint32_t address,
                                            std::uint32_t block_size) const {
    // assert that address is a valid block address
    assert(address % block_size == 0);

    std::vector<std::uint8_t> block(block_size);
    for (int i = 0; i < block_size; i++) {
        block[i] = data_[address + i];
    }
    return block;
}

void Memory::WriteBlock(std::uint32_t address, std::vector<std::uint8_t> data) {
    // assert that address is a valid block address
    assert(address % data.size() == 0);

    for (int i = 0; i < data.size(); i++) {
        data_[address + i] = data[i];
    }
}
