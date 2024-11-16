#include "matrix_chain.hpp"

int main() {

    int n;
    std::cin >> n;

    if (!std::cin.good() || n <= 1) {
        std::cout << print_red("Incorrect input matrix chain size\n");
        return 1;
    }

    std::vector<unsigned> sizes(n);
    for (int i = 0; i < n; ++i) {
        int size;
        std::cin >> size;
        if (!std::cin.good() || size <= 0) {
            std::cout << print_red("Incorrect input " << i + 1 << " matrix size\n");
            return 1;
        }
        sizes[i] = size;
    }
    
    matrix_chain::matrix_chain_t chain{sizes.begin(), sizes.end()};

    chain.print_order(std::cout);
    chain.multiply_chain_fast();
    return 0;
}