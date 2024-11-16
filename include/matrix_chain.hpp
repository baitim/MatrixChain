#pragma once

#include "matrix.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
#include <set>

namespace matrix_chain {

    class dp_chain_t {
    protected:
        std::vector<unsigned> sizes_;
        std::vector<unsigned> order_;
        unsigned cost_;
    
    private:
        struct dp_path_t final {
            unsigned x = 0;
            unsigned y = 0;
            unsigned oper = 0;
            dp_path_t() {}
            dp_path_t(unsigned x_, unsigned y_, unsigned oper_) : x(x_), y(y_), oper(oper_) {}
        };
        using path_container_t = std::vector<std::vector<std::pair<dp_path_t, dp_path_t>>>;
        
        std::vector<unsigned> get_optimal_path(
            const path_container_t& path) const {

            std::vector<unsigned> ans;
            std::stack<dp_path_t> opers;
            std::set<unsigned> used_opers;
            unsigned i, j;
            i = j = path.size() - 1;

            opers.push(path[i][j].first);
            opers.push(path[i][j].second);

            while (!opers.empty()) {
                dp_path_t oper = opers.top();

                if (i > 0 &&
                    j > 0 &&
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
            reverse(ans.begin(), ans.end());

            return ans;
        }

        void print_dp(const std::vector<std::vector<long long>>& dp) {
            for (int i = 0, end = dp.size(); i < end; ++i) {
                for (int j = 0; j < end; ++j)
                    std::cout << "[" 
                              << dp[i][j] << ",\t"
                              << sizes_[std::max(0, j - i)] << ",\t"
                              << sizes_[j + 1] << "]\t";
                std::cout << "\n";
            }
        }

        void print_path(const path_container_t& path) {
            for (int i = 0, end = path.size(); i < end; ++i) {
                for (int j = 0; j < end; ++j)
                    std::cout << "[" << path[i][j].first.x << ",\t"
                                     << path[i][j].first.y << "]\t\t";
                std::cout << "\n";
            }
            std::cout << "---------------------------------------------\n";
            for (int i = 0, end = path.size(); i < end; ++i) {
                for (int j = 0; j < end; ++j)
                    std::cout << "[" << path[i][j].second.x << ",\t"
                                     << path[i][j].second.y << "]\t\t";
                std::cout << "\n";
            }
        }

        void update_order() {
            const unsigned dp_size = sizes_.size() - 1;
            std::vector<std::vector<long long>> dp;
            path_container_t path;
            dp.assign  (dp_size, std::vector<long long>(dp_size, -1));
            path.assign(dp_size, std::vector<std::pair<dp_path_t, dp_path_t>>(dp_size));

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
                    std::cout << "\n";
                    print_path(path);
                    std::cout << "\n";
                    std::cout << "\n";
#endif
                }
            }

            cost_ = dp[dp_size - 1][dp_size - 1];
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
                pseudo_matrices.push_back({prev, *it, 1});
                prev = *it;
            }
        }

        void add_matrix(unsigned size) {
            push(size);
            pseudo_matrices.push_back({sizes_.back(), size, 1});
        }

        matrix::matrix_t<unsigned> multiply_chain_naive() {
            // matrix::matrix_t<unsigned> res = pseudo_matrices[0];
           
            // for (int i = 1, end = pseudo_matrices.size(); i < end; ++i) {
            //     matrix::matrix_t<unsigned> tmp{std::move(res)};
            //     res = tmp * pseudo_matrices[i];
            // }
            // return res;
            return pseudo_matrices[0];
        }

        matrix::matrix_t<unsigned> multiply_chain_fast() {
            // matrix::matrix_t<unsigned> res = pseudo_matrices[order_[0]] * pseudo_matrices[order_[0] + 1];
        
            // for (int i = 1, end = order_.size(); i < end; ++i) {
            //     matrix::matrix_t<unsigned> tmp{std::move(res)};

            //     std::cerr << "order: " << order_[i] << "\n";
            //     std::cerr << "tmp :\n" << tmp << "\n";

            //     if (order_[i] > order_[i - 1]) {//std::cerr << "mul 1 :\n" << pseudo_matrices[order_[i] + 1] << "\n";
            //         res = tmp * pseudo_matrices[order_[i] + 1]; }
            //     else{//std::cerr << "mul 2 :\n" << pseudo_matrices[order_[i]] << "\n";
            //         res = pseudo_matrices[order_[i]] * tmp; }
            // }
            // return res;
            return pseudo_matrices[0];
        }
    };

    std::ostream& operator<<(std::ostream& os, const matrix_chain_t& chain) {
        return chain.print_order(os);
    }
};