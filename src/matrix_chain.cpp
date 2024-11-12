#include "matrix_chain.hpp"

int main() {

    int n;
    std::cin >> n;

    if (!std::cin.good() || n <= 1) {
        std::cout << print_red("Incorrect input matrix chain size\n");
        return 1;
    }

    unsigned chain_size = n;
    std::vector<int> sizes(chain_size);

    for (int i = 0; i < n; ++i)
        std::cin >> sizes[i];
    
    matrix_chain::matrix_chain_t chain{sizes.begin(), sizes.end()};

    chain.print_procedure(std::cout);
    return 0;
}