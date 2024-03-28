#ifndef __PLRU_H__
#define __PLRU_H__

#include "bitvector.h"

class PLRU {
   public:
    /**
     * @brief Construct a new PLRU object
     *
     */
    explicit PLRU(unsigned int num_ways);

    /**
     * @brief Get the index of the least recently used way
     *
     * @return unsigned int
     */
    unsigned int lru_index() const;

    /**
     * @brief Update the PLRU state after an access to a way
     *
     * @param way
     */
    void access(unsigned int way);

    /**
     * @brief Get the PLRU state
     *
     * @return BitVector&
     */
    BitVector& state() { return bv_; }

    /**
     * @brief pretty print the state tree
     * 
     */
    void print_state_tree() const;

    /**
     * @brief Visualize the access to a way
     * 
     * @param way 
     */
    void visualize_access(unsigned int way);



   private:
    /**
     * @brief Get the index of the left child
     * 
     * @param idx 
     * @return unsigned int 
     */
    static unsigned int left_child(unsigned int idx)  { return 2 * idx + 1; }

    /**
     * @brief get the index of the right child
     * 
     * @param idx 
     * @return unsigned int 
     */
    static unsigned int right_child(unsigned int idx)  { return 2 * idx + 2; }

    void print_state_tree(const std::string& prefix, unsigned int idx, bool is_left) const;


    unsigned int num_ways_;
    unsigned int num_bits_;
    BitVector bv_;
};

#endif  // __PLRU_H__