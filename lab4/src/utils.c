#include "utils.h"

char* ReadString(FILE* stream) 
{
    if(feof(stream)) {
        return NULL;
    }

    const int chunkSize = 256;
    char* buffer = (char*)malloc(chunkSize);
    int bufferSize = chunkSize;

    if(buffer == NULL) 
    {
        printf("Couldn't allocate buffer");
        exit(EXIT_FAILURE);
    }

    int readChar;
    int idx = 0;

    while ((readChar = getc(stream)) != EOF) 
    {
        buffer[idx++] = readChar;

        if (idx == bufferSize) 
        {
            buffer = realloc(buffer, bufferSize + chunkSize);
            bufferSize += chunkSize;
        }

        if (readChar == '\n') {
            break;
        }
    }

    buffer[idx] = '\0';

    return buffer;
}

int ChoosePipe(char* str)
{
    char* vowels = {"AEIOUYaeiouy"};
    int vowelsCnt = 0;

    char* consonants = {
        "BCDFGHJKLMNPQRSTVWXYZbcdfghjklmnpqrstvwxyz"
    };
    int consonantsCnt = 0;

    for (int i = 0; i < (int)strlen(str); ++i)
    {
        int isVowel = 0;

        for (int j = 0; j < (int)strlen(vowels); ++j){
            if (str[i] == vowels[j])
            {
                ++vowelsCnt;
                isVowel = 1;
                break;
            }
        }

        if (isVowel){
            continue;
        }

        for (int j = 0; j < (int)strlen(consonants); ++j){
            if (str[i] == consonants[j])
            {
                ++consonantsCnt;
                break;
            }
        }
    }

    return vowelsCnt > consonantsCnt;
}
