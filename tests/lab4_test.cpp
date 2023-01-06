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

TEST(FourthLabTest, TestWithIO) 
{
    const char* fileWithInput = "input.txt";
    const char* fileWithOutput1 = "output1.txt";
    const char* fileWithOutput2 = "output2.txt";

    std::vector<std::string> input = {
        "lorem",
        "ipsum",
        "dolor",
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaapch-hi",
        "sit",
        "boooob",
        "1234pyaat",
        "amet",
        "ameet",
        "a",
        "b"
    };

    std::vector<std::string> expectedOutput1 = {
        "pch-h",
        "bb",
        "mt",
        "1234pt"
    };

    std::vector<std::string> expectedOutput2 = {
        "lrm",
        "psm",
        "dlr",
        "st",
        "mt",
        "b"
    };

    std::ofstream fout(fileWithInput);

    fout << fileWithOutput1 << '\n';
    fout << fileWithOutput2 << '\n';

    for (const auto &line : input){
        fout << line << '\n';
    }

    fout.close();

    FILE* fin = fopen(fileWithInput, "r");

    ParentRoutine(fin);

    fclose(fin);

    std::ifstream fin1(fileWithOutput1);
    std::ifstream fin2(fileWithOutput2);

    std::string strRes;
    std::vector<std::string> vecRes1;

    while (fin1 >> strRes){
        vecRes1.push_back(strRes);
    }

    std::vector<std::string> vecRes2;
    
    while (fin2 >> strRes){
        vecRes2.push_back(strRes);
    }

    fin1.close();
    fin2.close();

    std::stable_sort(vecRes1.begin(), vecRes1.end());
    std::stable_sort(vecRes2.begin(), vecRes2.end());

    std::stable_sort(expectedOutput1.begin(), expectedOutput1.end());
    std::stable_sort(expectedOutput2.begin(), expectedOutput2.end());

    for (int i = 0; i < (int)vecRes1.size(); ++i){
        EXPECT_EQ(vecRes1[i].c_str(), expectedOutput1[i].c_str());
    }

    for (int i = 0; i < (int)vecRes2.size(); ++i){
        EXPECT_EQ(vecRes2[i].c_str(), expectedOutput2[i].c_str());
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
