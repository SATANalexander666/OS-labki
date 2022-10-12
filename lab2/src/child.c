#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>

void ChildRoutine(int fd[2])
{
    close(fd[1]);

    char outPath[512];
    if (read(fd[0], &outPath, 512) == -1)
    {
        perror("reading from pipe error )");
        exit(EXIT_FAILURE);
    }

    FILE* output = fopen(outPath, "w");
    if (output == NULL)
    {
        perror("writing to file error )");
        exit(EXIT_FAILURE);
    }

    char vowels[13] = {"AEIOUYaeiouy"};
    char str[512];
    int end = 0;

    while (1)
    {
        if (read(fd[0], &end, sizeof(int)) == -1)
        {
            perror("reading from pipe error )");
            exit(EXIT_FAILURE);
        }

        if (end != 0){
            break;
        }

        if (read(fd[0], &str, 512) == -1)
        {
            perror("reading from pipe error )");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < (int)strlen(str); ++i)
        {
            int isVowel = 0;

            for (int j = 0; j < (int)strlen(vowels); ++j){
                if (str[i] == vowels[j]){
                    isVowel = 1;
                }
            }

            if (isVowel == 0){
                fprintf(output, "%c", str[i]);
            }
        }
        fprintf(output, "\n"); 
    }
    fclose(output);
    close(fd[0]);
}