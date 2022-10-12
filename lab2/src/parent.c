#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

#include<child.h>

int ChoosePipe(){
    return (int)rand() % 100 < 80;
}

void ParentRoutine(FILE* input)
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
        ChildRoutine(fd1);
    }
    else if (pid2 == 0){
        ChildRoutine(fd2);
    }
    else
    {
        close(fd1[0]);
        close(fd2[0]);

        char outPath1[512];
        char outPath2[512];

        fscanf(input, "%s", outPath1);
        fscanf(input, "%s", outPath2);

        write(fd1[1], &outPath1, 512);
        write(fd2[1], &outPath2, 512);

        char strInput[512];
        int end = 0;

        while(fscanf(input, "%s", strInput) != EOF)
        {
            if (ChoosePipe())
            {
                write(fd1[1], &end, sizeof(int));
                write(fd1[1], &strInput, 512);
            }
            else
            {
                write(fd2[1], &end, sizeof(int));
                write(fd2[1], &strInput, 512);
            }
        }

        end = 1;
        write(fd1[1], &end, sizeof(int));
        write(fd2[1], &end, sizeof(int));

        wait(&pid1);
        wait(&pid2);
    }
}

        /*
        close(fd1[0]);
        close(fd2[0]);

        char outPath1[512];
        //char outPath2[512];

        fscanf(input, "%s", outPath1);
        //fscanf(input, "%s", outPath2);

        write(fd1[1], &outPath1, 512);
        //write(fd2[1], &outPath2, 512);

        char data1[512][512];
        char data2[512][512];

        int dataSize1 = 0;
        int dataSize2 = 0;
        char strInput[512];

        while(fscanf(input, "%s", strInput) != EOF)
        {
            if (ChoosePipe() != -1)
            {
                strcpy(data1[dataSize1], strInput);
                ++dataSize1;
            }
            else
            {
                strcpy(data2[dataSize2], strInput);
                ++dataSize2;
            }
        }

        write(fd1[1], &dataSize1, sizeof(int));
        write(fd2[1], &dataSize2, sizeof(int));

        for (int i = 0; i < dataSize1; ++i){
            write(fd1[1], &data1[i], 512);
        }

        for (int i = 0; i < dataSize2; ++i){
            write(fd2[1], &data2[i], 512);
        }

        close(fd1[1]);
        close(fd2[1]);

        wait(&pid1);
    }
}
*/