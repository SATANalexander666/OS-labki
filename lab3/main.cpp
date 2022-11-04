#include <bits/stdc++.h>

#include "utils.hpp"
#include "body.hpp"

int main()
{
    std::vector<int> arr;

    for (int i = 0; i < 16; ++i){
        arr.push_back(GetRandomInt(0, 32));
    }

    for (int elem : arr){
        std::cout << elem << " ";
    }
    std::cout << '\n';

    TimSort(arr, 2);

    for (int elem : arr){
        std::cout << elem << " ";
    }
    std::cout << '\n';

    return 0;
}