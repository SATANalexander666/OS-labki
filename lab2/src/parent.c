#include "parent.h"
#include "utils.h"

int ChoosePipe(){
    return (int)rand() % 100 < 80;
}

void ParentRoutine(const char* pathToChild, FILE* input)
{
    char outPath1[SIZE];
    char outPath2[SIZE];

    fscanf(input, "%s\n", outPath1);
    fscanf(input, "%s\n", outPath2);

    int fd1[2], fd2[2];

    if (pipe(fd1) == -1 || pipe(fd2) == -1)
    {
        perror("pipe error )");
        exit(EXIT_FAILURE);
    }

    int pid1 = fork();
    int pid2 = 1;

    if (pid1 > 0){
        pid2 = fork();
    }

    if (pid1 < 0 || pid2 < 0)
    {
        perror("process error )");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0)
    {
        close(fd1[1]);

        dup2(fd1[0], 0);

        char *argv[3];
        argv[0] = malloc(strlen(pathToChild) + 1);
        strcpy(argv[0], pathToChild);
        argv[1] = malloc(strlen(outPath1) + 1);
        strcpy(argv[1], outPath1);
        argv[2] = NULL;

        execv(pathToChild, argv);    
    }
    else if (pid2 == 0)
    {
        close(fd2[1]);

        dup2(fd2[0], 0);

        char *argv[3];
        argv[0] = malloc(strlen(pathToChild) + 1);
        strcpy(argv[0], pathToChild);
        argv[1] = malloc(strlen(outPath2) + 1);
        strcpy(argv[1], outPath2);
        argv[2] = NULL;

        execv(pathToChild, argv);    
    }
    else
    {
        close(fd1[0]);
        close(fd2[0]);

        char strInput[SIZE];

        while (fscanf(input, "%s", strInput) != EOF)
        {
            if (ChoosePipe()){
                if (write(fd1[1], &strInput, SIZE) == -1)
                {
                    perror("writing to pipe error )");
                    exit(EXIT_FAILURE);
                }
            }
            else{
                if (write(fd2[1], &strInput, SIZE) == -1)
                {
                    perror("writing to pipe error )");
                    exit(EXIT_FAILURE);
                }
            }
        }

        close(fd1[1]);
        close(fd2[1]);

        wait(&pid1);
        wait(&pid2);
    }
}