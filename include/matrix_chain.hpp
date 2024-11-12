#pragma once

#include "ANSI_colors.hpp"
#include <iostream>
#include <vector>

namespace matrix_chain {
    class matrix_chain_t final {
        std::vector<int> sizes_;

    public:
        template <typename It>
        matrix_chain_t(It start, It fin) : sizes_(start, fin) {}

        void add_matrix(int size) {
            sizes_.push_back(size);
        }

        std::vector<int> get_procedure() const {
            return sizes_;
        }

        std::ostream& print(std::ostream& os) const {
            os << print_lblue("Matrix Chain:\n");
            for (auto i : sizes_)
                os << print_lblue(i << " ");
            os << "\n";
            return os;
        }

        void print_procedure(std::ostream& os) const {
            for (auto i : sizes_)
                os << i << " ";
            os << "\n";
        }
    };

    std::ostream& operator<<(std::ostream& os, const matrix_chain_t& chain) {
        return chain.print(os);
    }
};