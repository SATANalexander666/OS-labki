#include<parent.h>
#include<utils.h>

int ChoosePipe(){
    return (int)rand() % 100 < 80;
}

void ParentRoutine(const char* pathToChild, FILE* input)
{
    int field1[2], field2[2];

    if (pipe(field1) == -1 || pipe(field2) == -1)
    {
        perror("creating pipe error )");
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
        close(field1[1]);

        char* pipeName;
        int pipeNameSize;

        if (read(field1[0], &pipeNameSize, sizeof(int)) == -1)
        {
            perror("reading from pipe error");
            exit(EXIT_FAILURE);
        }

        pipeName = malloc(pipeNameSize);

        if (read(field1[0], &pipeName, pipeNameSize) == -1)
        {
            perror("reading from pipe error");
            exit(EXIT_FAILURE);
        }

        close(field1[0]);

        char *argv[3];
        argv[0] = malloc(strlen(pathToChild) + 1);
        strcpy(argv[0], pathToChild);
        argv[1] = malloc(pipeNameSize);
        strcpy(argv[1], pipeName);
        argv[2] = NULL;

        execv(pathToChild, argv);    
    }
    else if (pid2 == 0)
    {
        close(field2[1]);

        char* pipeName;
        int pipeNameSize;

        if (read(field2[0], &pipeNameSize, sizeof(int)) == -1)
        {
            perror("reading from pipe error");
            exit(EXIT_FAILURE);
        }

        pipeName = malloc(pipeNameSize);

        if (read(field2[0], &pipeName, pipeNameSize) == -1)
        {
            perror("reading from pipe error");
            exit(EXIT_FAILURE);
        }

        close(field2[0]);

        char *argv[3];
        argv[0] = malloc(strlen(pathToChild) + 1);
        strcpy(argv[0], pathToChild);
        argv[1] = malloc(pipeNameSize);
        strcpy(argv[1], pipeName);
        argv[2] = NULL;

        execv(pathToChild, argv);  
    }
    else
    {
        close(field1[0]);
        close(field2[0]);

        const char* pipeName1 = "ParentToChild1";
        const char* pipeName2 = "ParentToChild2";

        const int pipeNameSize1 = strlen(pipeName1) + 1;
        const int pipeNameSize2 = strlen(pipeName2) + 1;

        if (write(field1[1], &pipeNameSize1, sizeof(int)) == -1)
        {
            perror("writing to pipe error )");
            exit(EXIT_FAILURE);
        }

        if (write(field2[1], &pipeNameSize2, sizeof(int)) == -1)
        {
            perror("writing to pipe error )");
            exit(EXIT_FAILURE);
        }

        if (write(field1[1], &pipeName1, pipeNameSize1) == -1)
        {
            perror("writing to pipe error )");
            exit(EXIT_FAILURE);
        }

        if (write(field2[1], &pipeName2, pipeNameSize2) == -1)
        {
            perror("writing to pipe error )");
            exit(EXIT_FAILURE);
        }

        close(field1[1]);
        close(field2[1]);

        if (mkfifo(pipeName1, 0777) == -1){
            if (errno != EEXIST)
            {
                perror("creating named pipe error )");
                exit(EXIT_FAILURE);
            }
        }

        if (mkfifo(pipeName2, 0777) == -1){
            if (errno != EEXIST)
            {
                perror("creating named pipe error )");
                exit(EXIT_FAILURE);
            }
        }

        char outPath1[SIZE];
        char outPath2[SIZE];

        fscanf(input, "%s", outPath1);
        fscanf(input, "%s", outPath2);

        int fd1 = open(pipeName1, O_WRONLY);
        int fd2 = open(pipeName2, O_WRONLY);

        if (write(fd1, &outPath1, SIZE) == -1)
        {
            perror("writing to pipe error )");
            exit(EXIT_FAILURE);
        }
        
        if (write(fd2, &outPath2, SIZE) == -1)
        {
            perror("writing to pipe error )");
            exit(EXIT_FAILURE);
        }

        char strInput[SIZE];

        while (fscanf(input, "%s", strInput) != EOF)
        {
            if (ChoosePipe()){
                if (write(fd1, &strInput, SIZE) == -1)
                {
                    perror("writing to pipe error )");
                    exit(EXIT_FAILURE);
                }
            }
            else{
                if (write(fd2, &strInput, SIZE) == -1)
                {
                    perror("writing to pipe error )");
                    exit(EXIT_FAILURE);
                }
            }
        }

        close(fd1);
        close(fd2);

        wait(&pid1);
        wait(&pid2);
    }
}