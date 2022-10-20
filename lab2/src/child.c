#include<child.h>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        perror("Too few arguments )");
        exit(EXIT_FAILURE);
    }

    FILE* output = fopen(argv[1], "w");

    if (output == NULL)
    {
        perror("writing to file error )");
        exit(EXIT_FAILURE);
    }

    char* vowels = {"AEIOUYaeiouy"};

    for (int k = 2; k < argc; ++k)
    {
        for (int i = 0; i < (int)strlen(argv[k]); ++i)
        {
            int isVowel = 0;

            for (int j = 0; j < (int)strlen(vowels); ++j){
                if (argv[k][i] == vowels[j]){
                    isVowel = 1;
                }
            }

            if (isVowel == 0){
                fprintf(output, "%c", argv[k][i]);
            }
        }
        fprintf(output, "\n"); 
    }
    
    fclose(output);

    return 0;
}