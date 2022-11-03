#include <bits/stdc++.h>

#include "utils.hpp"
#include "body.hpp"

void MakeTest(std::string path)
{
    std::ofstream fout(path);
    fout << "out/1.txt" << '\n';

    for (int i = 0; i < 32; ++i){
        fout << GetRandomInt(0, 128) << '\n';
    }

    fout.close();
}

int main()
{
    std::string path = "in/1.txt";

    MakeTest(path);

    std::ifstream fin(path);
    Routine(fin, 16);
    fin.close();

    return 0;
}