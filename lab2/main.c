#include<stdio.h>

#include<parent.h>
#include<child.h>

int main()
{
    FILE* input = fopen("input", "r");

    if (input != NULL)
    {
        ParentRoutine(input);
        fclose(input);
    }

    return 0;
}
