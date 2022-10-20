#include<stdio.h>
#include<parent.h>

void CreateFile (const char* fileName)
{
    FILE* output = fopen(fileName, "w");

    if (output == NULL)
    {
        perror("openning file error )");
        exit(EXIT_FAILURE);
    }
    else
    {
        fprintf(output, "%s\n", "Output1.txt");
        fprintf(output, "%s\n", "Output2.txt");
        fprintf(output, "%s\n", "Work");
        fprintf(output, "%s\n", "Labochka");
        fprintf(output, "%s\n", "Work");
    }

    fclose(output);
}

int main()
{
    const char* fileName = "input.txt";
    CreateFile(fileName);

    FILE* input = fopen(fileName, "r");

    if (input == NULL)
    {
        perror("openning file error )");
        exit(EXIT_FAILURE);
    }
    else
    {
        ParentRoutine(getenv("PATH_TO_CHILD"), input);
        fclose(input);
    }

    return 0;
}
