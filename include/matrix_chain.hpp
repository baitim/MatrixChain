#pragma once

#include "matrix.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>

namespace matrix_chain {

    class dp_chain_t {
    protected:
        std::vector<unsigned> sizes_;
        std::vector<unsigned> order_;
        unsigned cost_;
    
    private:
        unsigned get_max_scope(const std::vector<std::vector<std::pair<unsigned, unsigned>>>& path) const {
            unsigned max = 0;
            for (int i = 0, end = path.size(); i < end; ++i)
                for (int j = i; j < end; ++j)
                    max = std::max(max, path[i][j].second);
            return max + 1;
        }

        std::vector<unsigned> get_optimal_path(
            const std::vector<std::vector<std::pair<unsigned, unsigned>>>& path) const {

            std::vector<std::vector<unsigned>> scopes(get_max_scope(path));
            unsigned i, j;
            i = j = path.size() - 1;
            while (i > 0) {
                scopes[path[i][j].second].push_back(i - 1);
                if (path[i][j].first == 1 + path[i - 1][j - 1].first) {
                    i--;
                    j--;
                } else if (i > 0 && path[i][j].first == 1 + path[i - 1][j].first) {
                    i--;
                } else {
                    break;
                }
            }

            std::vector<unsigned> ans;
            for (int i = scopes.size() - 1; i >= 0; --i) {
                auto& scope = scopes[i];
                sort(scope.begin(), scope.end());
                for (int size : scope)
                    ans.push_back(size);
            }

            return ans;
        }

        struct dp_elem_t final {
            long long cost = 0;
            unsigned x;
            unsigned y;
            dp_elem_t() {}
            dp_elem_t(unsigned x_, unsigned y_) : x(x_), y(y_) {}
            dp_elem_t(long long cost_, unsigned x_, unsigned y_) : cost(cost_), x(x_), y(y_) {}
        };

        void print_dp(const std::vector<std::vector<dp_elem_t>>& dp) {
            for (int i = 0, end = dp.size(); i < end; ++i) {
                for (int j = 0; j < end; ++j)
                    std::cout << "[" << dp[i][j].cost << ",\t"
                                     << dp[i][j].x    << ",\t"
                                     << dp[i][j].y    << "]\t";
                std::cout << "\n";
            }
        }

        void print_path(const std::vector<std::vector<std::pair<unsigned, unsigned>>>& path) {
            for (int i = 0, end = path.size(); i < end; ++i) {
                for (int j = 0; j < end; ++j)
                    std::cout << "[" << path[i][j].first  << ",\t"
                                     << path[i][j].second << "]\t";
                std::cout << "\n";
            }
        }

        void update_order() {
            const unsigned dp_size = sizes_.size() - 1;
            std::vector<std::vector<dp_elem_t>> dp;
            std::vector<std::vector<std::pair<unsigned, unsigned>>> path; // path, scope
            dp.assign  (dp_size, std::vector<dp_elem_t>(dp_size));
            path.assign(dp_size, std::vector<std::pair<unsigned, unsigned>>(dp_size, {0, 1}));

            for (unsigned i = 0; i < dp_size; ++i)
                for (unsigned j = 0; j < dp_size; ++j)
                    dp[i][j] = {sizes_[j], sizes_[j + 1]};

            for (unsigned i = 1; i < dp_size; ++i) {
                dp[1][i] = {sizes_[i - 1] * sizes_[i] * sizes_[i + 1], sizes_[i - 1], sizes_[i + 1]};
                path[1][i] = {i, 1};
            }

            for (unsigned i = 1; i < dp_size; ++i) {
                for (unsigned j = i + 1; j < dp_size; ++j) {
                    unsigned next_row = i + 1;
                    unsigned prev_col = j - 1;

                    // new matrix to scope
                    for (int row = i; row >= 0; --row) {
                        if (dp[i][prev_col].y != dp[row][j].x)
                            continue;
                        
                        unsigned x = dp[i][prev_col].x * dp[row][j].x * dp[row][j].y;
                        unsigned new_cost = x + dp[i][prev_col].cost;
                        
                        if (dp[next_row][j].cost == 0 ||
                            dp[next_row][j].cost > new_cost) {

                            path[next_row][j] = {path[i][prev_col].first + 1, path[row][j].second};
                            dp[next_row][j].cost = new_cost;
                            dp[next_row][j].x = dp[i][prev_col].x;
                        }
                    }

                    // new scope to scope
                    for (int col = j; col >= 0; --col) {
                        if (dp[i][col].y != dp[i][j].x)
                            continue;

                        unsigned x = dp[i][col].x * dp[i][j].x * dp[i][j].y;
                        unsigned new_cost = x + dp[i][j].cost;
                        
                        if (dp[next_row][j].cost == 0 ||
                            dp[next_row][j].cost > new_cost) {

                            path[next_row][j] = {path[i][j].first + 1, path[i][j].second + 1};
                            dp[next_row][j].cost = new_cost;
                            dp[next_row][j].x = dp[i][j].x;
                        }
                    }

#ifdef DEBUG
                    print_dp(dp);
                    std::cout << "\n";
                    print_path(path);
                    std::cout << "\n";
                    std::cout << "\n";
#endif
                }
            }

            cost_ = dp[dp_size - 1][dp_size - 1].cost;
            if (cost_ == 0) {
                order_.resize(sizes_.size() - 2);
                std::iota(order_.begin(), order_.end(), 0);
            } else {
                order_ = get_optimal_path(path);
            }
        }

    public:
        template <typename It>
        dp_chain_t(It start, It end) : sizes_(start, end) {
            update_order();
        }

        void push(unsigned size) {
            sizes_.push_back(size);
            update_order();
        }

        std::ostream& print_order(std::ostream& os) const {
            for (auto i : order_)
                os << i << " ";
            os << "\n";
            return os;
        }

        std::vector<unsigned> get_order() const { return order_; }

        virtual ~dp_chain_t() {};
    };

    class matrix_chain_t final : dp_chain_t {
        using dp_chain_t::sizes_;
        using dp_chain_t::order_;
        std::vector<matrix::matrix_t<unsigned>> pseudo_matrices;

    public:
        using dp_chain_t::print_order;
        using dp_chain_t::get_order;

        template <typename It>
        matrix_chain_t(It start, It end) : dp_chain_t(start, end) {
            if (sizes_.size() < 2)
                throw;

            auto it = start;
            unsigned prev = *it++;
            for (int i = 0; it != end; ++it, ++i) {
                pseudo_matrices.push_back({prev, *it});
                prev = *it;
            }
        }

        void add_matrix(unsigned size) {
            push(size);
            pseudo_matrices.push_back({sizes_.back(), size});
        }

        matrix::matrix_t<unsigned> multiply_chain_naive() {
            matrix::matrix_t<unsigned> res = pseudo_matrices[0];
            for (int i = 1, end = sizes_.size(); i < end; ++i)
                res = res * pseudo_matrices[i];
            return res;
        }

        matrix::matrix_t<unsigned> multiply_chain_fast() {
            matrix::matrix_t<unsigned> res = pseudo_matrices[order_[0]];
            for (int i = 1, end = order_.size(); i < end; ++i)
                res = res * pseudo_matrices[order_[i]];
            return res;
        }
    };

    std::ostream& operator<<(std::ostream& os, const matrix_chain_t& chain) {
        return chain.print_order(os);
    }
};