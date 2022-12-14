#include "parent.h"
#include "utils.h"

int ChoosePipe(){
    return (int)rand() % 100 < 80;
}

void ParentRoutine(char* pathToChild, FILE* fin)
{
    char* fileName1 = ReadString(fin);
    char* fileName2 = ReadString(fin);

    fileName1[strlen(fileName1) - 1] = '\0';
    fileName2[strlen(fileName2) - 1] = '\0';

    unlink(fileName1);
    unlink(fileName2);

    int fd1[2], fd2[2];

    if (pipe(fd1) == -1 || pipe(fd2) == -1)
    {
        perror("creating pipe error )");
        exit(EXIT_FAILURE);
    }

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

    char* argv[2];
    argv[0] = "child";
    argv[1] = NULL;

    pid_t pid1 = fork();
    pid_t pid2 = 1;

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

        if (dup2(fd1[0], 0) < 0)
        {
            perror("duping pipe error )");
            exit(EXIT_FAILURE);
        }

        if (dup2(outputFile1, 1) < 0)
        {
            perror("duping output file error )");
            exit(EXIT_FAILURE);
        }

        execv(pathToChild, argv);

        //perror("execv error )");
        //exit(EXIT_FAILURE);
    }
    else if (pid2 == 0)
    {
        close(fd2[1]);

        if (dup2(fd2[0], 0) < 0)
        {
            perror("duping pipe error )");
            exit(EXIT_FAILURE);
        }

        if (dup2(outputFile2, 1) < 0)
        {
            perror("duping output file error )");
            exit(EXIT_FAILURE);
        }

        execv(pathToChild, argv);

        //perror("execv error )");
        //exit(EXIT_FAILURE);
    }
    else
    {
        close(fd1[0]);
        close(fd2[0]);

        char* strInput = NULL;

        while ((strInput = ReadString(fin)) != NULL)
        {
            int strSize = strlen(strInput);

            if (strSize > 0)
            {
                if (ChoosePipe())
                {
                    write(fd1[1], strInput, strSize);
                }
                else 
                {
                    write(fd2[1], strInput, strSize);
                }
            }

            free(strInput);
        }

        if (strInput == NULL)
        {
            char terminator = '\0';

            write(fd1[1], &terminator, 1);
            write(fd2[1], &terminator, 1);
        }

        close(fd1[1]);
        close(fd2[1]);
    }
}
