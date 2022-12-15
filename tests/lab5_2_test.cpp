#include <gtest/gtest.h>
#include <vector>
#include <math.h>

extern "C"{
    #include "libLab5.h"
}

struct TIArgs {
    double a, b, epsilon;
};

struct TDArgs {
    double a, deltaX;
};

TEST(FifthSecondLabTest, IntegrateTest)
{
    std::vector<TIArgs> input = {
        {0, 1, 0.001},
        {0, 2, 0.0001},
        {-6, 7, 0.00001},
        {-100, 100, 0.0000000000001}
    };

    std::vector<double> expectedOutput ={
        0.45969,
        1.41614,
        0.20626,
        0
    };
    
    constexpr double epsilon = 0.001;

    std::vector<double> output;

    for (TIArgs args : input){
        output.push_back(Integrate(args.a, args.b, args.epsilon));
    }

    for (int i = 0; i < (int)output.size(); ++i){
        EXPECT_GE(epsilon, fabs(expectedOutput[i] - output[i]));
    }
}

TEST(FifthSecondLabTest, DerivativeTest)
{
    std::vector<TDArgs> input = {
        {0, 0.001},
        {1, 0.0001},
        {-6, 0.00001},
        {-100, 0.0000000000001}
    };

    std::vector<double> expectedOutput ={
        0,
        -0.84147,
        -0.27941,
        -0.50636
    };
    
    constexpr double epsilon = 0.01;

    std::vector<double> output;

    for (TDArgs args : input){
        output.push_back(Derivative(args.a, args.deltaX));
    }

    for (int i = 0; i < (int)output.size(); ++i){
        EXPECT_GE(epsilon, fabs(expectedOutput[i] - output[i]));
    }
}

