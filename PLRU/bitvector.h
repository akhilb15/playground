#ifndef __BITVECTOR_H__
#define __BITVECTOR_H__

#include <stdint.h>

#include <iostream>

class BitVector {
   public:
    /**
     * @brief Construct a new Bit Vector object
     *
     */
    BitVector() : size_(0), bits_(0) {}
    explicit BitVector(unsigned int size) : size_(size) { bits_ = 0; }
    BitVector(unsigned int size, uint64_t bits) : size_(size), bits_(bits) {}

    /**
     * @brief Set a bit in the bit vector
     *
     * @param idx
     * @param val
     */
    void set(unsigned int idx, bool val) {
        if (val) {
            bits_ |= (1 << idx);
        } else {
            bits_ &= ~(1 << idx);
        }
    }

    /**
     * @brief Get a bit from the bit vector
     *
     * @param idx
     * @return bool, whether the bit is set
     */
    bool get(unsigned int idx) const { return ((bits_ >> idx) & 1) != 0U; }

    /**
     * @brief Get a bit from the bit vector
     *
     * @param idx
     * @return bool, whether the bit is set
     */
    bool operator[](unsigned int idx) const { return get(idx); }

    /**
     * @brief Get the size of the bit vector
     *
     * @return unsigned int
     */
    unsigned int size() const { return size_; }

    /**
     * @brief print the bits in the bit vector
     *
     * @param output stream
     * @param bit vector
     * @return std::ostream&
     */
    friend std::ostream& operator<<(std::ostream& os, const BitVector& bv) {
        for (unsigned int i = 0; i < bv.size_; i++) {
            os << static_cast<unsigned int>(bv.get(i)) << " ";
        }
        return os;
    }

   private:
    unsigned int size_;
    uint64_t bits_;
};

#endif  // __BITVECTOR_H__