#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <cstdint>
#include <vector>

class Memory {
   public:
    explicit Memory(std::uint32_t size);

    std::uint8_t ReadByte(int address) const;
    void WriteByte(int address, std::uint8_t value);

    std::vector<std::uint8_t> ReadBlock(std::uint32_t address,
                                        std::uint32_t block_size) const;
    void WriteBlock(std::uint32_t address, std::vector<std::uint8_t> data);

    int size() const;

   private:
    std::uint32_t size_ = 0;
    std::vector<std::uint8_t> data_;
};

#endif  // __MEMORY_H__