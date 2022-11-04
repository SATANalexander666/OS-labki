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

double GetAvgTime(std::vector<int> &data, const int numOfThreads)
{
    constexpr int runsCount = 10;
    double avg = 0;

    for(int i = 0; i < runsCount; ++i) 
    {
        std::vector<int> changingData = data;
        auto begin = std::chrono::high_resolution_clock::now();
        Routine(changingData, numOfThreads);
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

    Routine(inputData, numOfThreads);
    std::stable_sort(checkData.begin(), checkData.end());

    ASSERT_TRUE(inputData.size() == checkData.size());

    for (int i = 0; i < (int)checkData.size(); ++i){
        EXPECT_EQ(inputData[i], checkData[i]);
    }
}

TEST(ThridLabTest, PerfomanceTest)
{
    auto perfomanceTest = [](const int size, const int numOfThreads)
    {
        std::vector<int> inputData = GenerateVector(size);
        std::vector<int> checkData = inputData;

        Routine(inputData, numOfThreads);
        std::stable_sort(checkData.begin(), checkData.end());

        ASSERT_TRUE(inputData.size() == checkData.size());

        for (int i = 0; i < (int)checkData.size(); ++i){
            EXPECT_EQ(inputData[i], checkData[i]);
        }
    };

    for (int i = 4; i < 14; ++i){
        perfomanceTest(128 * i, i);
    }   
}

TEST(ThridLabTest, ComparisonTest)
{
    std::vector<int> inputData = GenerateVector(16384);
    const int numOfThreads1 = 1;
    const int numOfThreads2 = 12;

    double singleThread = GetAvgTime(inputData, numOfThreads1);
    double multiThread = GetAvgTime(inputData, numOfThreads2);

    std::cout << "Avg time for 1 thread: " << singleThread << '\n';
    std::cout << "Avg time for " << numOfThreads2 << " threads: " << multiThread << '\n';

    EXPECT_GE(singleThread, multiThread);
}

TEST(ThridLabTest, MultiThreadEfficiencyTest)
{
    std::vector<int> inputData = GenerateVector(16384);
    
    for (int numOfThreads = 2; numOfThreads <= 16; numOfThreads += 2)
    {
        double time = GetAvgTime(inputData, numOfThreads);
        
        std::cout << "Avg time for " << numOfThreads << " threads: " << time << '\n';
    }
}