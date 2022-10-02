#include<iostream>
#include<string>
#include<set>
#include<algorithm>

#include<child.hpp>

#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    int pid = fork();
    std::string a = "Ae132Yboi";

    if (pid != 0){
        wait(&pid);
    }
    else{
        RemoveVowels(a);
    }

    for (char elem : a){
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}