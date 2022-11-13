#include "parent.h"

int ChoosePipe(char* str)
{
    char* vowels = {"AEIOUYaeiouy"};
    vowelsCnt = 0;

    for (int i = 0; i < (int)strlen(str); ++i){
        for (int j = 0; j < (int)strlen(vowels); ++j){
            if (str[i] = vowels[j]){
                ++vowelsCnt;
            }
        }
    }
}

