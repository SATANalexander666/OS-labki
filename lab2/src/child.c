#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "utils.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        perror("too few arguments )");
        exit(EXIT_FAILURE);
    }

    int readState = 1;
    char* vowels = {"AEIOUYaeiouy"};

    FILE* output = fopen(argv[1], "w");

    if (output == NULL)
    {
        perror("writing to file error )");
        exit(EXIT_FAILURE);
    }

    char str[SIZE];

    while (scanf("%s", str) != EOF)
    {
        for (int i = 0; i < (int)strlen(str); ++i)
        {
            int is_vowel = 0;

            for (int j = 0; j < (int)strlen(vowels); ++j){
                if (str[i] == vowels[j])
                {
                    is_vowel = 1;
                    break;
                }
            }

            if (is_vowel == 0){
                fprintf(output, "%c", str[i]);
            }
        }

        fprintf(output, "\n");
    }

    fclose(output);

    return 0;
}