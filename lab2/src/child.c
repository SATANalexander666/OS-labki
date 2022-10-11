#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>

void ChildRoutine(int fd[2])
{
    close(fd[1]);

    char outPath[512];
    read(fd[0], &outPath, 512);

    int dataSize;
    read(fd[0], &dataSize, sizeof(int));

    char str[512];
    char vowels[13] = {"AEIOUYaeiouy"};

    FILE* output = fopen(outPath, "w");

    if (output == NULL)
    {
        perror("file error )");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < dataSize; ++i)
    {
        read(fd[0], &str, 512);
            
        for (int j = 0; j < (int)strlen(str); ++j)
        {
            int isVowel = 0;
            for (int k = 0; k < (int)strlen(vowels); ++k){
                if (str[j] == vowels[k]){
                    isVowel = 1;
                }
            }

            if (isVowel == 0){
                fprintf(output, "%c", str[j]);
            }
        }

        fprintf(output, "\n");    
    }
        fclose(output);
        close(fd[0]);
}