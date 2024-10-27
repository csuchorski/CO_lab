#include <cmath>
#include <cstdio>
#include <vector>
#include <array>
#include <iostream>
#include <algorithm>
#include <tuple>

// https://www.hackerrank.com/contests/ok-homeworks/challenges/count-distinct-elements-1-2

int block_size;

bool compare_queries(const std::tuple<int, int, int> &A, const std::tuple<int, int, int> &B)
{
    int A_block = std::get<0>(A) / block_size;
    int B_block = std::get<0>(B) / block_size;

    if (A_block != B_block)
    {
        return A_block < B_block;
    }

    return std::get<1>(A) < std::get<1>(B);
}

void remove_at(int index, std::vector<int> &counter, int &distinct_c)
{
    if (counter.at(index) == 1)
    {
        distinct_c--;
    }
    counter[index]--;
}

void add_at(int index, std::vector<int> &counter, int &distinct_c)
{
    counter[index]++;
    if (counter[index] == 1)
    {
        distinct_c++;
    }
}

int main()
{
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++)
    {
        int n;
        std::cin >> n;
        block_size = sqrt(n);
        std::vector<int> nums(n);
        std::vector<int> counter(1000001);
        // counter.fill(0);
        int distinct_c = 0;

        for (int j = 0; j < n; j++)
        {
            std::cin >> nums[j];
        }
        int q;
        std::cin >> q;
        std::vector<std::tuple<int, int, int>> queries(q);
        std::vector<int> results(q);
        for (int j = 0; j < q; j++)
        {
            int x, y;
            std::cin >> x >> y;
            queries[j] = {x, y, j};
        }
        std::sort(queries.begin(), queries.end(), compare_queries);
        int left = 0;
        int right = -1;
        for (std::tuple<int, int, int> query : queries)
        {
            while (left < std::get<0>(query))
            {
                remove_at(nums[left], counter, distinct_c);
                left++;
            }
            while (left > std::get<0>(query))
            {
                left--;
                add_at(nums[left], counter, distinct_c);
            }
            while (right < std::get<1>(query))
            {
                right++;
                add_at(nums[right], counter, distinct_c);
            }
            while (right > std::get<1>(query))
            {
                remove_at(nums[right], counter, distinct_c);
                right--;
            }
            results[std::get<2>(query)] = distinct_c;
        }
        for (int res : results)
        {
            std::cout << res << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
