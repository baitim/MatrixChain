#include "matrix_chain.hpp"
#include <gtest/gtest.h>

template <typename ElemT>
void is_vectors_eq(const std::vector<ElemT>& v1, const std::vector<ElemT>& v2,
                   const std::string& msg = "") {
    ASSERT_EQ(v1.size(), v2.size());
    for (int i = 0, end = v1.size(); i < end; ++i)
        EXPECT_EQ(v1[i], v2[i]) << " at index: " << i << " " << msg << "\n";
}

TEST(Matrix_chain_main, test_simple_1)
{
    std::vector<unsigned> ans;
    std::vector<unsigned> sizes = {30, 35, 15};

    matrix_chain::matrix_chain_t chain{sizes.begin(), sizes.end()};

    chain.add_matrix(5);
    chain.add_matrix(10);

    ans = chain.get_order();
    is_vectors_eq(ans, {1, 0, 2}, "test simple 1");

    ASSERT_EQ(chain.multiply_chain_fast().first, chain.multiply_chain_naive().first);
    ASSERT_EQ(chain.multiply_chain_fast().second, 9375);
}

TEST(Matrix_chain_main, test_simple_2)
{
    std::vector<unsigned> ans;
    std::vector<unsigned> sizes = {10, 30, 5, 60};

    matrix_chain::matrix_chain_t chain{sizes.begin(), sizes.end()};

    ans = chain.get_order();
    is_vectors_eq(ans, {0, 1}, "test simple 2");

    ASSERT_EQ(chain.multiply_chain_fast().first, chain.multiply_chain_naive().first);
    ASSERT_EQ(chain.multiply_chain_fast().second, 4500);
}

TEST(Matrix_chain_main, test_zero)
{
    std::vector<unsigned> ans;
    std::vector<unsigned> sizes = {30, 20, 10};

    matrix_chain::matrix_chain_t<short> chain{sizes.begin(), sizes.end()};

    chain.add_matrix(1);
    chain.add_matrix(20);
    chain.add_matrix(30);

    ans = chain.get_order();
    is_vectors_eq(ans, {1, 0, 3, 2}, "test zero");

    ASSERT_EQ(chain.multiply_chain_fast().first, chain.multiply_chain_naive().first);
    ASSERT_EQ(chain.multiply_chain_fast().second, 2300);
}

TEST(Matrix_chain_main, test_split_muls)
{
    std::vector<unsigned> ans;
    std::vector<unsigned> sizes = {5, 15, 7, 17, 5};

    matrix_chain::matrix_chain_t<unsigned> chain{sizes.begin(), sizes.end()};

    ans = chain.get_order();
    is_vectors_eq(ans, {0, 2, 1}, "test split muls");

    ASSERT_EQ(chain.multiply_chain_fast().first, chain.multiply_chain_naive().first);
    ASSERT_EQ(chain.multiply_chain_fast().second, 1295);
}