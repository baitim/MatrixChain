#pragma once

#include "ANSI_colors.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

namespace matrix_chain {

    class dp_chain_t {
        std::vector<int> sizes_;
        std::vector<int> order_;
    
    private:
        int get_max_scope(const std::vector<std::vector<std::pair<int, int>>>& path) const {
            int max = -1;
            for (int i = 0, end = path.size(); i < end; ++i)
                for (int j = i; j < end; ++j)
                    max = std::max(max, path[i][j].second);
            return max + 1;
        }

        std::vector<int> get_optimal_path(const std::vector<std::vector<std::pair<int, int>>>& path) const {
            std::vector<std::vector<int>> scopes(get_max_scope(path));
            int i, j;
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

            std::vector<int> ans;
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
            int x;
            int y;
            dp_elem_t() {}
            dp_elem_t(int x_, int y_) : x(x_), y(y_) {}
            dp_elem_t(long long cost_, int x_, int y_) : cost(cost_), x(x_), y(y_) {}
        };

        void print_dp(const std::vector<std::vector<dp_elem_t>>& dp) {
            for (int i = 0, end = dp.size(); i < end; ++i) {
                for (int j = 0; j < end; ++j)
                    std::cout << "[" << dp[i][j].cost << ",\t" << dp[i][j].x << ",\t" << dp[i][j].y << "]\t";
                std::cout << "\n";
            }
        }

        void print_path(const std::vector<std::vector<std::pair<int, int>>>& path) {
            for (int i = 0, end = path.size(); i < end; ++i) {
                for (int j = 0; j < end; ++j)
                    std::cout << "[" << path[i][j].first << ",\t" << path[i][j].second << "]\t";
                std::cout << "\n";
            }
        }

        void update_order() {
            const int dp_size = sizes_.size() - 1;
            std::vector<std::vector<dp_elem_t>> dp;
            std::vector<std::vector<std::pair<int, int>>> path; // path, scope
            dp.assign  (dp_size, std::vector<dp_elem_t>(dp_size));
            path.assign(dp_size, std::vector<std::pair<int, int>>(dp_size, {0, 1}));

            for (int i = 0; i < dp_size; ++i)
                for (int j = 0; j < dp_size; ++j)
                    dp[i][j] = {sizes_[j], sizes_[j + 1]};

            for (int i = 1; i < dp_size; ++i) {
                dp[1][i] = {sizes_[i - 1] * sizes_[i] * sizes_[i + 1], sizes_[i - 1], sizes_[i + 1]};
                path[1][i] = {i, 1};
            }

            for (int i = 1; i < dp_size; ++i) {
                for (int j = i + 1; j < dp_size; ++j) {
                    int next_row = i + 1;
                    int prev_col = j - 1;

                    for (int row = i; row >= 0; --row) {
                        if (dp[i][prev_col].y != dp[row][j].x)
                            continue;
                        
                        int x = dp[i][prev_col].x * dp[row][j].x * dp[row][j].y;
                        int new_cost = x + dp[i][prev_col].cost;
                        
                        if (dp[next_row][j].cost == 0 ||
                            dp[next_row][j].cost > new_cost) {

                            path[next_row][j] = {path[i][prev_col].first + 1, path[row][j].second};
                            dp[next_row][j].cost = new_cost;
                            dp[next_row][j].x = dp[i][prev_col].x;
                        }
                    }

                    for (int col = j; col >= 0; --col) {
                        if (dp[i][col].y != dp[i][j].x)
                            continue;

                        int x = dp[i][col].x * dp[i][j].x * dp[i][j].y;
                        int new_cost = x + dp[i][j].cost;
                        
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

            order_ = get_optimal_path(path);
        }

    public:
        template <typename It>
        dp_chain_t(It start, It end) : sizes_(start, end) {
            update_order();
        }

        void add_elem(int size) {
            sizes_.push_back(size);
            update_order();
        }

        void print_order(std::ostream& os) const {
            for (auto i : order_)
                os << i << " ";
            os << "\n";
        }

        std::vector<int> get_order() const { return order_; }

        virtual ~dp_chain_t() {};
    };

    class matrix_chain_t final : dp_chain_t {
    public:
        using dp_chain_t::print_order;
        using dp_chain_t::get_order;

        template <typename It>
        matrix_chain_t(It start, It end) : dp_chain_t(start, end) {}

        void add_matrix(int x) {
            add_elem(x);
        }

        std::ostream& print(std::ostream& os) const {
            os << print_lblue("Matrix Chain\n");
            return os;
        }
    };

    std::ostream& operator<<(std::ostream& os, const matrix_chain_t& chain) {
        return chain.print(os);
    }
};