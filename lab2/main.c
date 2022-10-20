#include<stdio.h>
#include<parent.h>
#include<child.h>

int main()
{
    FILE* input = fopen("input.txt", "r");

    if (input == NULL)
    {
        perror("openning file error )");
        exit(EXIT_FAILURE);
    }
    else
    {
        ParentRoutine("./child", input);
        fclose(input);
    }

    return 0;
}
