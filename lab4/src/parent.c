#include "parent.h"
#include "utils.h"

#include <sys/param.h>

void ParentRoutine(FILE* fin)
{
    char* fileName1 = ReadString(fin);
    char* fileName2 = ReadString(fin);

    fileName1[strlen(fileName1) - 1] = '\0';
    fileName2[strlen(fileName2) - 1] = '\0';

    unlink(fileName1);
    unlink(fileName2);

    pid_t outputFile1, outputFile2;

    if ((outputFile1 = open(fileName1, O_WRONLY | O_CREAT, S_IRWXU)) < 0) 
    {
        perror("opening output file 1 error )");
        exit(EXIT_FAILURE);
    }

    if ((outputFile2 = open(fileName2, O_WRONLY | O_CREAT, S_IRWXU)) < 0) 
    {
        perror("opening output file 2 error )");
        exit(EXIT_FAILURE);
    }

    free(fileName1);
    free(fileName2);



    const int mapSize = 16;

    unlink("mappedFile1");
    unlink("mappedFile2");

    int  mappedFfile1 = open("mappedFile1", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    int  mappedFfile2 = open("mappedFile2", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    if (mappedFfile1 == -1 || mappedFfile2 == -1) 
    {
        perror("open error");
        exit(EXIT_FAILURE);
    }

    if (ftruncate(mappedFfile1, mapSize) == -1) 
    {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    if (ftruncate(mappedFfile2, mapSize) == -1) 
    {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }



    const char* semFile1 = "semaphore1";
    const char* semFile2 = "semaphore2";

	sem_t* sem1 = sem_open(semFile1, O_CREAT, S_IRUSR | S_IWUSR, 0);
	sem_t* sem2 = sem_open(semFile2, O_CREAT, S_IRUSR | S_IWUSR, 0);

    const char* vowels = {"AEIOUYaeiouy"};

    pid_t pid1 = fork();
    pid_t pid2 = 1;

    if (pid1 > 0){
        pid2 = fork();
    }

    if (pid1 < 0 || pid2 < 0)
    {
        perror("Creating process error )");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) 
    {
        if (dup2(outputFile1, 1) < 0)
        {
            perror("dup2() error )");
            exit(EXIT_FAILURE);
        }

        void* map = mmap(NULL, mapSize, PROT_READ, MAP_SHARED,  mappedFfile1, 0);

        sem_t* sem = sem_open(semFile1, 0);

        while (1)
        {
            char* str = (char*)malloc(mapSize);

            sem_wait(sem);
            memcpy(str, map, mapSize);

            for (int i = 0; i < (int)strlen(str); ++i)
            {
                int isVowel = 0;

                for (int j = 0; j < (int)strlen(vowels); ++j)
                {
                    if (str[i] == vowels[j])
                    {
                        isVowel = 1;
                        break;
                    }
                }

                if (isVowel == 0) {
                    printf("%c", str[i]);
                }
            }

            if (str[0] == '\0')
            {
                free(str);
                break;
            }

            free(str);
        }

        munmap(map, mapSize);
        close(outputFile2);
    }
    else if (pid2 == 0)
    {
        if (dup2(outputFile2, 1) < 0)
        {
            perror("dup2() error )");
            exit(EXIT_FAILURE);
        }

        void* map = mmap(NULL, mapSize, PROT_READ, MAP_SHARED,  mappedFfile2, 0);

        sem_t* sem = sem_open(semFile2, 0);

        while (1)
        {
            char* str = (char*)malloc(mapSize);

            sem_wait(sem);
            memcpy(str, map, mapSize);

            for (int i = 0; i < (int)strlen(str); ++i)
            {
                int isVowel = 0;

                for (int j = 0; j < (int)strlen(vowels); ++j)
                {
                    if (str[i] == vowels[j])
                    {
                        isVowel = 1;
                        break;
                    }
                }

                if (isVowel == 0) {
                    printf("%c", str[i]);
                }
            }

            if (str[0] == '\0')
            {
                free(str);
                break;
            }

            free(str);
        }

        munmap(map, mapSize);
        close(outputFile2);
    }
    else 
    {
        void* map1 = mmap(NULL, mapSize, PROT_WRITE, MAP_SHARED,  mappedFfile1, 0);
        void* map2 = mmap(NULL, mapSize, PROT_WRITE, MAP_SHARED,  mappedFfile2, 0);

        char* strInput = NULL;

        while ((strInput = ReadString(fin)) != NULL)
        {
            int numOfParts = strlen(strInput) / mapSize + 1;

            if (ChoosePipe(strInput))
            {
                for (int i = 0; i < numOfParts; ++i)
                {
                    char* part = (char*)malloc(mapSize);
                    memmove(part, strInput, mapSize);
                    strcpy(&strInput[0], &strInput[mapSize]);

                    memcpy(map1, part, mapSize);
                    sem_post(sem1);

                    free(part);
                }
            }
            else
            {
                for (int i = 0; i < numOfParts; ++i)
                {
                    char* part = (char*)malloc(mapSize);
                    memmove(part, strInput, mapSize);
                    strcpy(&strInput[0], &strInput[mapSize]);

                    memcpy(map2, part, mapSize);
                    sem_post(sem2);

                    free(part);
                }
            }

            free(strInput);
        }

        char* terminator = "\0";

        memcpy(map1, terminator, 1);
        sem_post(sem1);

        memcpy(map2, terminator, 1);
        sem_post(sem2);

        munmap(map1, mapSize);
        munmap(map2, mapSize);
    }

    unlink("mappedFile1");
    unlink("mappedFile2");

    sem_close(sem1);
    sem_close(sem2);

	sem_unlink(semFile1);
	sem_unlink(semFile2);
}