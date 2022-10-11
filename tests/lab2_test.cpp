#include <gtest/gtest.h>

#include <array>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>

namespace fs = std::filesystem;

extern "C" {
    #include <parent.h>
}

TEST(FirstLabTests, SimpleTest) {
    const char* fileWithInput = "input.txt";
    const char* fileWithOutput = "output.txt";

    constexpr int inputSize = 5;

    std::array<const char*, inputSize> input = {
        "1234aaron",
        "aezakmi",
        "Work",
        "labochka",
        "Work"
    };

    std::array<const char*, inputSize> expectedOutput = {
        "1234rn",
        "zkm",
        "Wrk",
        "lbchk",
        "Wrk"
    };

    {
        auto inFile = std::ofstream(fileWithInput);

        inFile << fileWithOutput << '\n';

        for(const auto& line : input) {
            inFile<< line << '\n';
        }
    }

    auto deleter = [](FILE* file) {
        fclose(file);
    };

    std::unique_ptr<FILE, decltype(deleter)> inFile(fopen(fileWithInput, "r"), deleter);

    ParentRoutine(inFile.get());

    auto outFile = std::ifstream(fileWithOutput);

    ASSERT_TRUE(outFile.good());

    std::string strRes;
    for(const char* i : expectedOutput)
    {
        outFile >> strRes;
        EXPECT_STREQ(strRes.c_str(), i);
    }

    /*
    auto removeIfExists = [](const char* path) {
        if(fs::exists(path)) {
            fs::remove(path);
        }
    };

    removeIfExists(fileWithInput);
    removeIfExists(fileWithOutput);
    */
}