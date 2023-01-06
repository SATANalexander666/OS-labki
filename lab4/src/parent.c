#include "parent.h"
#include "utils.h"
#include <semaphore.h>

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

    const int mapSize = 128;

    void* map1 = mmap(0, mapSize, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
    void* map2 = mmap(0, mapSize, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);

	sem_t* sem1 = sem_open("semaphore1", O_CREAT, S_IRUSR | S_IWUSR, 0);
	sem_t* sem2 = sem_open("semaphore2", O_CREAT, S_IRUSR | S_IWUSR, 0);

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

        char* str = (char*)malloc(mapSize);

		sem_wait(sem1);
        msync(map1, mapSize, MS_SYNC);
        memcpy(str, map1, mapSize);

        for (int i = 0; i < (int)strlen(str); ++i)
        {
            int isVowel = 0;

            for (int j = 0; j < (int)strlen(vowels); ++j){
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
    }
    else if (pid2 == 0)
    {
        if (dup2(outputFile2, 1) < 0)
        {
            perror("dup2() error )");
            exit(EXIT_FAILURE);
        }

        char* str = (char*)malloc(mapSize);

		sem_wait(sem2);
        msync(map1, mapSize, MS_SYNC | MS_INVALIDATE);
        memcpy(str, map2, mapSize);

        for (int i = 0; i < (int)strlen(str); ++i)
        {
            int isVowel = 0;

            for (int j = 0; j < (int)strlen(vowels); ++j){
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
    }
    else 
    {
        char* strInput = NULL;

        const int chunkSize = 16;

        int bufferSize1 = chunkSize;
        int freeSpace1 = bufferSize1;

        char* buffer1 = (char*)malloc(chunkSize);

        int bufferSize2 = chunkSize;
        int freeSpace2 = bufferSize2;

        char* buffer2 = (char*)malloc(chunkSize);

        while ((strInput = ReadString(fin)) != NULL)
        {
            if (ChoosePipe(strInput))
            {
                while (freeSpace1 < (int)strlen(strInput))
                {
                    buffer1 = (char*)realloc(buffer1, bufferSize1 + chunkSize);

                    bufferSize1 += chunkSize;
                    freeSpace1 += chunkSize;
                }

                strcat(buffer1, strInput);
                freeSpace1 -= strlen(strInput);

                free(strInput);
            }
            else
            {
                while (freeSpace2 < (int)strlen(strInput))
                {
                    buffer2 = (char*)realloc(buffer2, bufferSize2 + chunkSize);

                    bufferSize2 += chunkSize;
                    freeSpace2 += chunkSize;
                }

                strcat(buffer2, strInput);
                freeSpace2 -= strlen(strInput);

                free(strInput);
            }
        }

        memcpy(map1, buffer1, strlen(buffer1));
        msync(map1, mapSize, MS_SYNC | MS_INVALIDATE);
		sem_post(sem1);

        memcpy(map2, buffer2, strlen(buffer2));
        msync(map2, mapSize, MS_SYNC | MS_INVALIDATE);
		sem_post(sem2);

		wait(&pid1);
		wait(&pid2);
    }

    munmap(map1, mapSize);
    munmap(map2, mapSize);
    
    sem_close(sem1);
    sem_close(sem2);
	sem_unlink("semaphore1");
	sem_unlink("semaphore2");
}
