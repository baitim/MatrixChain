#include "matrix_chain.hpp"
#include <gtest/gtest.h>

void is_vectors_eq(const std::vector<int>& v1, const std::vector<int>& v2) {
    ASSERT_EQ(v1.size(), v2.size());

    for (int i = 0, end = v1.size(); i < end; ++i)
        EXPECT_EQ(v1[i], v2[i]) << " at index: " << i << "\n";
}

TEST(Matrix_chain_main, test_simple)
{
    std::vector<int> ans;
    std::vector<int> sizes = {30, 35, 15};

    matrix_chain::matrix_chain_t chain{sizes.begin(), sizes.end()};

    chain.push(5);
    chain.push(10);

    ans = chain.get_order();
    is_vectors_eq(ans, {1, 0, 2});
}

TEST(Matrix_chain_main, test_zero)
{
    std::vector<int> ans;
    std::vector<int> sizes = {30, 20, 10};

    matrix_chain::matrix_chain_t chain{sizes.begin(), sizes.end()};

    chain.push(0);
    chain.push(20);
    chain.push(30);

    ans = chain.get_order();
    is_vectors_eq(ans, {0, 1, 2, 3});
}