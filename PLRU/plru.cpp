/**
 * @file plru.cpp
 * @author Akhil Bharanidhar
 * @brief PLRU class implementation
 * @version 0.1
 * @date 2023-11-15
 *
 */

#include "plru.h"

#define LEFT 0
#define RIGHT 1

PLRU::PLRU(unsigned int num_ways) : num_ways_(num_ways) {
    // Initialize the bit vector
    num_bits_ = num_ways_ - 1;
    bv_ = BitVector(num_bits_);
}

unsigned int PLRU::lru_index() const {
    // Return the least recently used way
    unsigned int idx = 0;
    while (idx < bv_.size()) {
        if (bv_[idx]) {
            idx = right_child(idx);
        } else {
            idx = left_child(idx);
        }
    }
    return idx - bv_.size();
}

void PLRU::access(unsigned int way) {
    // Update the PLRU state after an access to a way
    unsigned int idx = way + bv_.size();
    while (idx > 0) {
        unsigned int parent = (idx - 1) / 2;
        if (idx % 2 == 0) {  // if right child
            bv_.set(parent, LEFT);
        } else {  // if left child
            bv_.set(parent, RIGHT);
        }
        idx = parent;
    }
}

void PLRU::print_state_tree(const std::string& prefix, unsigned int idx, bool is_left) const {
    // Pretty print the state tree
    // leaf nodes should be ways
    // internal nodes should be L/R
    unsigned int lru_way = lru_index();

    if (idx < bv_.size()) {
        std::cout << prefix;
        std::cout << (is_left ? "├──" : "└──" );

        // print the value of the node
        std::cout << (bv_[idx] ? "R" : "L") << '\n';

        // compute the prefix for children
        std::string new_prefix = prefix + (is_left ? "│   " : "    ");
        print_state_tree(new_prefix, left_child(idx), true);
        print_state_tree(new_prefix, right_child(idx), false);
    } else {
        std::cout << prefix;
        std::cout << (is_left ? "├──" : "└──" );
        std::cout << "Way " << idx - bv_.size() << (lru_way == idx - bv_.size() ? " (LRU)" : "") << '\n';
    }
}

void PLRU::print_state_tree() const {
    // Pretty print the state tree
    std::cout << "\t* L points to top branch, R points to bottom branch" << "\n\n";
    print_state_tree("", 0, false);
    std::cout << '\n';
}


void PLRU::visualize_access(unsigned int way) {
    // Visualize the access to a way
    std::cout << "----------------------------------------\n";
    std::cout << "Accessed way " << way << '\n';
    access(way);
    print_state_tree();
    std::cout << "LRU way (after access): " << lru_index() << "\n\n";
    std::cout << "----------------------------------------\n";
}


