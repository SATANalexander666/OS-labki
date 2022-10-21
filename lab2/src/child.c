#include<child.h>
#include<utils.h>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        perror("too few arguments )");
        exit(EXIT_FAILURE);
    }

    char* pipeName = argv[1];
    int fd = open(pipeName, O_RDONLY);

    char outPath[SIZE];

    if (read(fd, &outPath, SIZE) == -1)
    {
        perror("reading from named pipe error");
        exit(EXIT_FAILURE);
    }

    char str[SIZE];
    int readState = 1;

    char* vowels = {"AEIOUYaeiouy"};

    FILE* output = fopen(outPath, "w");

    if (output == NULL)
    {
        perror("writing to file error )");
        exit(EXIT_FAILURE);
    }

    while ((readState = read(fd, &str, SIZE)) != 0)
    {
        if (readState == -1)
        {
            perror("reading from named pipe error");
            exit(EXIT_FAILURE);
        }

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
    close(fd);

    return 0;
}