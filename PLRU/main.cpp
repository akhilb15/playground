#include "plru.h"

int main() {
    PLRU plru(8);
    std::cout << "Initial state: " << '\n';
    plru.print_state_tree();
    std::cout << "LRU way: " << plru.lru_index() << "\n\n";

    for (unsigned int i = 0; i < 4; i++) {
        unsigned int random_way = rand() % 5;
        plru.visualize_access(random_way);
    }

    return 0;
}