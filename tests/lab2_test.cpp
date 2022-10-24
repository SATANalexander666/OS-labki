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
    #include <parent.h>
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
        "1234aaron"
    };

    std::vector<std::string> expectedOutput = {
        "Wrk",
        "lbchk",
        "Wrk",
        "1234rn"
    };

    {
        auto inFile = std::ofstream(fileWithInput);

        inFile << fileWithOutput1 << '\n';
        inFile << fileWithOutput2 << '\n';

        for (const auto& line : input){
            inFile << line << '\n';
        }
    }

    auto deleter = [](FILE* file) {
        fclose(file);
    };

    std::unique_ptr<FILE, decltype(deleter)> inFile(fopen(fileWithInput, "r"), deleter);
    
    ParentRoutine(getenv("PATH_TO_CHILD"), inFile.get());

    auto outFile1 = std::ifstream(fileWithOutput1);
    auto outFile2 = std::ifstream(fileWithOutput2);

    ASSERT_TRUE(outFile1.good());
    ASSERT_TRUE(outFile2.good());

    std::string strRes;
    std::vector<std::string> vecRes;

    while (outFile1 >> strRes){
        vecRes.push_back(strRes);
    }
    
    while (outFile2 >> strRes){
        vecRes.push_back(strRes);
    }

    std::stable_sort(vecRes.begin(), vecRes.end());
    std::stable_sort(expectedOutput.begin(), expectedOutput.end());

    ASSERT_TRUE(vecRes.size() == expectedOutput.size());

    for (int i = 0; i < (int)vecRes.size(); ++i){
        EXPECT_STREQ(vecRes[i].c_str(), expectedOutput[i].c_str());
    }
}