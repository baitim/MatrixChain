#include "MatrixChain/matrix_chain.hpp"

using namespace matrix_chain;

int main() try {

    size_t n;
    std::cin >> n;

    if (!std::cin.good() || n <= 2)
        throw matrix_chain::error_t{str_red("Incorrect input matrix chain size\n")};

    std::vector<unsigned> sizes(n);
    for (size_t i = 0; i < n; ++i) {
        unsigned size;
        std::cin >> size;
        if (!std::cin.good())
            throw matrix_chain::error_t{str_red(  "Incorrect input "
                                                + std::to_string(i + 1)
                                                + " matrix size(negtive)\n")};
        sizes[i] = size;
    }

    matrix_chain_t chain{sizes.begin(), sizes.end()};
    chain.print_order(std::cout);
    long long cost_mult_fast  = chain.multiply_chain_fast().second;
    long long cost_mult_naive = chain.get_cost_mult_naive();
    std::cout <<   static_cast<long double>(cost_mult_naive)
                 / static_cast<long double>(cost_mult_fast) << '\n';

} catch(const matrix_chain::error_t& error) {
    std::cout << error.what() << '\n';
    return 1;
} catch (...) {
    std::cout << print_red("Unknown error\n");
    return 1;
}