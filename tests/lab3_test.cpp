#include <gtest/gtest.h>
#include <chrono>

#include <vector>
#include <algorithm>

#include "body.hpp"
#include "utils.hpp"

std::vector<int> GenerateVector(const int size)
{
    std::vector<int> result;

    for (int i = 0; i < size; ++i){
        result.push_back(GetRandomInt(-1023, 1024));
    }

    return result;
}

double GetAvgTime(const int numOfThreads)
{
    constexpr int runsCount = 10;
    double avg = 0;

    for(int i = 0; i < runsCount; ++i) 
    {
        std::vector<int> data = GenerateVector(8371);
        auto begin = std::chrono::high_resolution_clock::now();
        TimSort(data, numOfThreads);
        auto end = std::chrono::high_resolution_clock::now();
        avg += std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    }

    return avg / runsCount;
}

TEST(ThridLabTest, SingleThreadTest)
{
    std::vector<int> inputData = GenerateVector(2048);
    std::vector<int> checkData = inputData;
    const int numOfThreads = 1;

    TimSort(inputData, numOfThreads);
    std::stable_sort(checkData.begin(), checkData.end());

    ASSERT_TRUE(inputData.size() == checkData.size());

    for (int i = 0; i < (int)checkData.size(); ++i){
        EXPECT_EQ(inputData[i], checkData[i]);
    }
}

TEST(ThridLabTest, ThreadsConfigurationsTest)
{
    auto runTest = [](const int size, const int numOfThreads)
    {
        std::vector<int> inputData = GenerateVector(size);
        std::vector<int> checkData = inputData;

        TimSort(inputData, numOfThreads);
        std::stable_sort(checkData.begin(), checkData.end());

        ASSERT_TRUE(inputData.size() == checkData.size());

        for (int i = 0; i < (int)checkData.size(); ++i){
            EXPECT_EQ(inputData[i], checkData[i]);
        }
    };

    runTest(1111, 2);   
    runTest(3321, 3);  
    runTest(5496, 5);   
    runTest(27983, 12);   
    runTest(45961, 16);   
}

TEST(ThridLabTest, ComparisonTest)
{
    const int numOfThreads1 = 1;
    const int numOfThreads2 = 12;

    double singleThread = GetAvgTime(numOfThreads1);
    double multiThread = GetAvgTime(numOfThreads2);

    std::cout << "Avg time for 1 thread: " << singleThread << '\n';
    std::cout << "Avg time for " << numOfThreads2 << " threads: " << multiThread << '\n';

    EXPECT_GE(singleThread, multiThread);
}