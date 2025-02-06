#include "MatrixChain/matrix_chain.hpp"

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
        if (!std::cin.good() || size < 0) {
            std::cout << print_red("Incorrect input " << i + 1 << " matrix size(negtive)\n");
            return 1;
        }
        sizes[i] = size;
    }
    
    try {
        matrix_chain::matrix_chain_t chain{sizes.begin(), sizes.end()};
        chain.print_order(std::cout);
        long long cost_mult_fast  = chain.multiply_chain_fast().second;
        long long cost_mult_naive = chain.get_cost_mult_naive();
        std::cout <<   static_cast<long double>(cost_mult_naive)
                     / static_cast<long double>(cost_mult_fast) << "\n";

    } catch(const matrix_chain::error_t& error) {
        std::cout << print_red(error.what()) << "\n";
        return 1;
    }
    return 0;
}