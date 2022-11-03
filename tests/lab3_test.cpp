#include <gtest/gtest.h>
#include <chrono>

#include <string>
#include <vector>
#include <algorithm>

#include <filesystem>
#include <memory>

namespace fs = std::filesystem;

#include "body.hpp"
#include "utils.hpp"

const int MIN = -1023;
const int MAX = 1024;

std::vector<int> PrepareData(
    std::string inPath, 
    std::string outPath, 
    const int size
)
{
    std::ofstream fout(inPath);
    fout << outPath << '\n';

    std::vector<int> data(size);

    for (int i = 0; i < size; ++i)
    {
        int num = GetRandomInt(MIN, MAX);
        fout << num << '\n';
        data[i] = num;
    }

    fout.close();

    std::sort(data.begin(), data.end());

    return data;
}

double GetAvgTime(std::string inPath, const int numOfThreads)
{
    constexpr int runsCount = 10;
    double avg = 0;

    for(int i = 0; i < runsCount; ++i) 
    {
        std::ifstream fin(inPath);

        auto begin = std::chrono::high_resolution_clock::now();
        Routine(fin, numOfThreads);
        auto end = std::chrono::high_resolution_clock::now();

        avg += std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

        fin.close();
    }

    return avg / runsCount;
}

void RemoveIfExists(std::string path) {
    if(fs::exists(path)) {
        fs::remove(path);
    }
}

TEST(ThirdLabTests, SingleThreadResult)
{
    std::string inPath = "input.txt";
    std::string outPath = "output.txt";
    const int inputSize = 32;

    std::vector<int> expectedOutput = PrepareData(
        inPath,
        outPath,
        inputSize
    );

    std::ifstream fin;

    fin.open(inPath);
    if (fin.good()){
        Routine(fin, 1);
    }
    fin.close();

    fin.open(outPath);
    ASSERT_TRUE(fin.good());

    int result;
    int i = -1;

    while (fin >> result){
        EXPECT_EQ(result, expectedOutput[++i]);
    }
    fin.close();

    RemoveIfExists(inPath);
    RemoveIfExists(outPath);
}

TEST(ThirdLabTests, MultiThreadResult)
{
    std::string inPath = "input.txt";
    std::string outPath = "output.txt";
    const int inputSize = 65536;

    std::vector<int> expectedOutput = PrepareData(
        inPath,
        outPath,
        inputSize
    );

    std::ifstream fin;
    const int numOfThreads = 16;

    fin.open(inPath);
    if (fin.good()){
        Routine(fin, numOfThreads);
    }
    fin.close();

    fin.open(outPath);
    ASSERT_TRUE(fin.good());

    int result;
    int i = -1;

    while (fin >> result){
        EXPECT_EQ(result, expectedOutput[++i]);
    }
    fin.close();

    RemoveIfExists(inPath);
    RemoveIfExists(outPath);
}

TEST(ThirdLabTests, PerfomanceTest)
{
    std::string inPath = "input.txt";
    std::string outPath = "output.txt";
    const int inputSize = 16384;

    PrepareData(
        inPath,
        outPath,
        inputSize
    );

    const int numOfThreads = 12;

    double singleThread = GetAvgTime(inPath, 1);
    double multiThread = GetAvgTime(inPath, numOfThreads);

    EXPECT_GE(singleThread, multiThread);

    std::cout << "Average time for 1 thread: " << singleThread << '\n';
    std::cout << "Average time for " << numOfThreads << " threads: " << multiThread << '\n';
}