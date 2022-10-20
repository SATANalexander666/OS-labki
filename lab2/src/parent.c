#include<parent.h>

int ChoosePipe(){
    return (int)rand() % 100 < 80;
}

void ChildRoutine(const char* pathToChild, int fd[2])
{
    close(fd[1]);

    char strInput[512];
    char* argv[512];

    if (read(fd[0], &strInput, 512) == -1)
    {
        perror("reading from pipe error )");
        exit(EXIT_FAILURE);
    }

    argv[0] = malloc(strlen(pathToChild) + 1);
    strcpy(argv[0], pathToChild);

    argv[1] = malloc(strlen(strInput) + 1);
    strcpy(argv[1], strInput);

    int end = 0;
    int k = 2;

    while (1)
    {
        if (read(fd[0], &end, sizeof(int)) == -1)
        {
            perror("reading from pipe error )");
            exit(EXIT_FAILURE);
        }

        if (end != 0){
            break;
        }

        if (read(fd[0], &strInput, 512) == -1)
        {
            perror("reading from pipe error )");
            exit(EXIT_FAILURE);
        }

        if (strInput != NULL)
        {    
            argv[k] = malloc(sizeof(strInput) + 1);
            strcpy(argv[k], strInput);
            ++k;
        }
    }

    argv[k] = NULL;

    close(fd[0]);
    
    printf("%s", pathToChild);
    if (execv(pathToChild, argv) == -1)
    {
        perror("child programm error )");
        exit(EXIT_FAILURE);
    }
}

void ParentRoutine(const char* pathToChild, FILE* input)
{
    int fd1[2], fd2[2];

    if (pipe(fd1) == -1 || pipe(fd2) == -1)
    {
        perror("pip error )");
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

    if (pid1 == 0){
        ChildRoutine(pathToChild, fd1);
    }
    else if (pid2 == 0){
        ChildRoutine(pathToChild, fd2);
    }
    else
    {
        close(fd1[0]);
        close(fd2[0]);

        char outPath1[512];
        char outPath2[512];

        fscanf(input, "%s", outPath1);
        fscanf(input, "%s", outPath2);

        if (write(fd1[1], &outPath1, 512) == -1)
        {
            perror("writing to pipe error )");
            exit(EXIT_FAILURE);
        }
        
        if (write(fd2[1], &outPath2, 512) == -1)
        {
            perror("writing to pipe error )");
            exit(EXIT_FAILURE);
        }

        char strInput[512];
        int end = 0;

        while(fscanf(input, "%s", strInput) != EOF)
        {
            if (ChoosePipe())
            {
                if (write(fd1[1], &end, sizeof(int)) == -1)
                {
                    perror("writing to pipe error )");
                    exit(EXIT_FAILURE);
                }

                if (write(fd1[1], &strInput, 512) == -1)
                {
                    perror("writing to pipe error )");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                if (write(fd2[1], &end, sizeof(int)) == -1)
                {
                    perror("writing to pipe error )");
                    exit(EXIT_FAILURE);
                }

                if (write(fd2[1], &strInput, 512) == -1)
                {
                    perror("writing to pipe error )");
                    exit(EXIT_FAILURE);
                }
            }
        }

        end = 1;
        if (write(fd1[1], &end, sizeof(int)) == -1)
        {
            perror("writing to pipe error )");
            exit(EXIT_FAILURE);
        }

        if (write(fd2[1], &end, sizeof(int)) == -1)
        {
            perror("writing to pipe error )");
            exit(EXIT_FAILURE);
        }

        wait(&pid1);
        wait(&pid2);
    }
}