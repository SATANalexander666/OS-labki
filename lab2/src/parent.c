#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

#include<child.h>

bool ChoosePipe()
{
    int choice = rand() % 100;

    return choice > 80;
}

void ParentRoutine(FILE* input)
{
    int fd[2];

    if (pipe(fd) == -1)
    {
        perror("pip error )");
        exit(EXIT_FAILURE);
    }

    int pid1 = fork();

    if (pid1 == -1)
    {
        perror("process error )");
        exit(EXIT_FAILURE);
    }
    else if (pid1 == 0)
    {
        ChildRoutine(fd);
    }
    else
    {
        close(fd[0]);

        char outPath[512];
        fscanf(input, "%s", outPath);
        write(fd[1], &outPath, 512);

        char data[512][512];
        char strInput[512];
        int dataSize = 0;

        while(fscanf(input, "%s", strInput) != EOF)
        {
            strcpy(data[dataSize], strInput);
            ++dataSize;
        }

        write(fd[1], &dataSize, sizeof(int));

        for (int i = 0; i < dataSize; ++i){
            write(fd[1], &data[i], 512);
        }

        close(fd[1]);

        wait(&pid1);
    }

}
    /*
    char outPath[SIZE];
    fscanf(input, "%s", outPath);

    FILE* output = fopen(outPath, "w");

    if (output != NULL)
    {
        char str[SIZE];
        char vowels[13] = {"AEIOUYaeiouy"};

        while (fscanf(input, "%s", str) != EOF)
        {
            for (int i = 0; i < (int)strlen(str); ++i)
            {
                int isVowel = 0;
                for (int j = 0; j < (int)strlen(vowels); ++j){
                    if (str[i] == vowels[j]){
                        isVowel = 1;
                    }
                }

                if (!isVowel){
                    fprintf(output, "%c", str[i]);        
                }
            }
            fprintf(output, "\n");
        }

        fclose(output);
    }
    */