#pragma once

#include "MatrixChain/ANSI_colors.hpp"
#include "Matrix/matrix.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>

namespace matrix_chain {

    using namespace matrix;

    class matrix_chain_error_t : public std::runtime_error {
    public:
        matrix_chain_error_t(std::string msg) : std::runtime_error(msg) {}
    };

    class dp_chain_t {
    protected:
        std::vector<unsigned> sizes_;
        std::vector<unsigned> order_;

    private:
        struct dp_path_t final {
            unsigned x = 0;
            unsigned y = 0;
            unsigned oper = 0;
        };
        using path_container_t = std::vector<std::vector<std::pair<dp_path_t, dp_path_t>>>;
        
        std::vector<unsigned> get_optimal_path(
            const path_container_t& path) const {

            std::vector<unsigned> ans;
            std::stack<dp_path_t, std::vector<dp_path_t>> opers;
            std::unordered_set<unsigned> used_opers;
            unsigned i, j;
            i = j = path.size() - 1;

            opers.push(path[i][j].first);
            opers.push(path[i][j].second);

            while (!opers.empty()) {
                dp_path_t oper = opers.top();

                if (i > 0 &&
                    used_opers.find(oper.oper) == used_opers.end()) {
                    ans.push_back(oper.oper);
                    used_opers.insert(oper.oper);
                }

                i = oper.x;
                j = oper.y;
                opers.pop();

                if (i > 0) {
                    opers.push(path[i][j].first);
                    opers.push(path[i][j].second);
                }
            }
            std::reverse(ans.begin(), ans.end());

            return ans;
        }

        void print_dp(const std::vector<std::vector<long long>>& dp) const {
            for (int i = 0, end = dp.size(); i < end; ++i) {
                for (int j = 0; j < end; ++j)
                    std::cout << '['
                              << dp[i][j] << ",\t"
                              << sizes_[std::max(0, j - i)] << ",\t"
                              << sizes_[j + 1] << "]\t";
                std::cout << '\n';
            }
        }

        void print_path(const path_container_t& path) const {
            for (int i = 0, end = path.size(); i < end; ++i) {
                for (int j = 0; j < end; ++j)
                    std::cout << '[' << path[i][j].first.x << ",\t"
                                     << path[i][j].first.y << "]\t\t";
                std::cout << '\n';
            }
            std::cout << "---------------------------------------------\n";
            for (int i = 0, end = path.size(); i < end; ++i) {
                for (int j = 0; j < end; ++j)
                    std::cout << '[' << path[i][j].second.x << ",\t"
                                     << path[i][j].second.y << "]\t\t";
                std::cout << '\n';
            }
        }

        void update_order() {
            const unsigned dp_size = sizes_.size() - 1;
            std::vector<std::vector<long long>> dp(dp_size, std::vector<long long>(dp_size, -1));
            path_container_t path(dp_size, std::vector<std::pair<dp_path_t, dp_path_t>>(dp_size));

            for (unsigned i = 0; i < dp_size; ++i)
                dp[0][i] = 0;

            for (unsigned i = 0; i < dp_size - 1; ++i) {
                for (unsigned j = i + 1; j < dp_size; ++j) {
                    unsigned next_row = i + 1;
                    for (int rrow = i; rrow >= 0; --rrow) {
                        unsigned rcol = j;
                        unsigned lrow = i - rrow;
                        unsigned lcol = j - rrow - 1;
                        if ((static_cast<int>(j) - rrow - 1) >= 0) {
                            unsigned x = sizes_[j - i - 1] * sizes_[lcol + 1] * sizes_[rcol + 1];
                            unsigned new_cost = x + dp[lrow][lcol] + dp[rrow][rcol];

                            if (dp[next_row][rcol] == -1 ||
                                dp[next_row][rcol] > new_cost) {

                                path[next_row][rcol].first  = {lrow, lcol, lcol};
                                path[next_row][rcol].second = {static_cast<unsigned>(rrow),  rcol, lcol};
                                dp[next_row][rcol] = new_cost;
                            }
                        }
                    }

#ifdef DEBUG
                    print_dp(dp);
                    std::cout << '\n';
                    print_path(path);
                    std::cout << '\n';
                    std::cout << '\n';
#endif
                }
            }

            order_ = get_optimal_path(path);
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
                os << i << ' ';
            os << '\n';
            return os;
        }

        std::vector<unsigned> get_order() const { return order_; }

        virtual ~dp_chain_t() {};
    };

    template <matrix_elem_t ElemT = unsigned long long>
    class matrix_chain_t final : dp_chain_t {
        using dp_chain_t::sizes_;
        using dp_chain_t::order_;
        std::vector<matrix_t<ElemT>> matrices;

        struct mult_block_t final {
            matrix_t<ElemT> m{0, 0};
            unsigned left  = -1;
            unsigned right = -1;
        };

    public:
        using dp_chain_t::print_order;
        using dp_chain_t::get_order;

        template <std::input_iterator It>
        requires matrix_elem_t<typename std::iterator_traits<It>::value_type> &&
                 std::convertible_to<typename std::iterator_traits<It>::value_type, unsigned> &&
                 std::default_initializable<ElemT>
        matrix_chain_t(It start, It end) : dp_chain_t(start, end) {
            if (sizes_.size() < 2)
                throw matrix_chain_error_t{str_red("size of chain less than 2")};

            auto it = start;
            unsigned prev = *it++;
            for (; it != end; ++it) {
                matrices.push_back({prev, *it, ElemT{}});
                prev = *it;
            }
        }

        void add_matrix(unsigned size) {
            matrices.push_back({sizes_.back(), size, 1});
            push(size);
        }

        matrix_t<ElemT> multiply_chain_naive() const {
            matrix_t<ElemT> res = matrices[0];
            long long cost = 0;
            for (int i = 1, end = matrices.size(); i < end; ++i) {
                matrix_t<ElemT> tmp{std::move(res)};
                cost += tmp.get_rows() * tmp.get_cols() * matrices[i].get_cols();
                res = tmp * matrices[i];
            }
            return res;
        }

        std::pair<matrix_t<ElemT>, long long> multiply_chain_fast() const {
            std::vector<mult_block_t> results;
            long long cost = 0;
            for (int i = 0, end = order_.size(); i < end; ++i) {
                if (!matrices[order_[i]])
                    return {{0, 0}, 0};
                
                matrix_t<ElemT> left  = matrices[order_[i]];
                matrix_t<ElemT> right = matrices[order_[i] + 1];;
                unsigned ind_left  = order_[i];
                unsigned ind_right = order_[i];
                for (int j = 0, end = results.size(); j < end; ++j) {
                    if (results[j].left - 1 == order_[i]) {
                        right = results[j].m;
                        ind_right = results[j].right;
                    }
                    if (results[j].right + 1 == order_[i]) {
                        left = results[j].m;
                        ind_left = results[j].left;
                    }
                }

                results.push_back({left * right, ind_left, ind_right});
                cost += left.get_cols() * left.get_rows() * right.get_cols();
            }
            return {results.back().m, cost};
        }

        long long get_cost_mult_naive() const {
            long long cost = 0;
            for (int i = 1, end = matrices.size(); i < end; ++i)
                cost += matrices[0].get_rows() * matrices[i - 1].get_cols() * matrices[i].get_cols();
            return cost;
        }
    };

    template <matrix_elem_t ElemT>
    std::ostream& operator<<(std::ostream& os, const matrix_chain_t<ElemT>& chain) {
        return chain.print_order(os);
    }
};