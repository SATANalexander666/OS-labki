#include<iostream>
#include<string>

#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

std::string Parent()
{
    std::string str1;

    std::cin >> str1;
    
    return str1;
}

void Child1(std::string str)
{
    std::cout << str << std::endl;
}

void Child2(std::string str)
{
    std::cout << str << std::endl;
}

int main()
{
    std::string str;

    int pid = fork();

    if (pid > 0)
    {
        std::cout << "Parent " << std::endl;
        str = Parent();
    }
    else if (pid == 0)
    {
        std::cout << "Child: ";
        Child1(str);
    }

    return 0;
}