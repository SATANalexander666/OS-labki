#ifndef OS_LABS_PARENT_H
#define OS_LABS_PARENT_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>

void ParentRoutine(const char* pathToChild, FILE* input);

#endif