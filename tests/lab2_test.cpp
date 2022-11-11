#include<gtest/gtest.h>

#include<filesystem>
#include<fstream>
#include<iostream>
#include<memory>

#include<vector>
#include<string>
#include<set>
#include<algorithm>

namespace fs = std::filesystem;

extern "C" {
    #include "parent.h"
}

TEST(SecondLabTest, TestWithIO) 
{
    const char* fileWithInput = "input.txt";
    const char* fileWithOutput1 = "output1.txt";
    const char* fileWithOutput2 = "output2.txt";

    std::vector<std::string> input = {
        "Work",
        "labochka",
        "Work",
        "1234aaron",
        "lorem",
        "ipsum",
        "dolor",
        "sit",
        "amet"
    };

    std::vector<std::string> expectedOutput = {
        "Wrk",
        "lbchk",
        "Wrk",
        "1234rn",
        "lrm",
        "psm",
        "dlr",
        "st",
        "mt"
    };

    std::ofstream fout(fileWithInput);

    fout << fileWithOutput1 << '\n';
    fout << fileWithOutput2 << '\n';

    for (const auto &line : input){
        fout << line << '\n';
    }

    fout.close();

    FILE* fin = fopen(fileWithInput, "r");

    ParentRoutine(getenv("PATH_TO_CHILD"), fin);

    fclose(fin);

    std::ifstream fin1(fileWithOutput1);
    std::ifstream fin2(fileWithOutput2);
    
    ASSERT_TRUE(fin1.good());
    ASSERT_TRUE(fin2.good());

    std::string strRes;
    std::vector<std::string> vecRes;

    while (fin1 >> strRes){
        vecRes.push_back(strRes);
    }
    
    while (fin2 >> strRes){
        vecRes.push_back(strRes);
    }

    fin1.close();
    fin2.close();

    std::stable_sort(vecRes.begin(), vecRes.end());
    std::stable_sort(expectedOutput.begin(), expectedOutput.end());

    for (int i = 0; i < (int)vecRes.size(); ++i){
        EXPECT_EQ(vecRes[i].c_str(), expectedOutput[i].c_str());
    }

    auto removeIfExists = [](const char* path) {
        if (fs::exists(path)) {
            fs::remove(path);
        }
    };

    removeIfExists(fileWithInput);
    removeIfExists(fileWithOutput1);
    removeIfExists(fileWithOutput2);
}