#ifndef OS_LABS_PARENT_H
#define OS_LABS_PARENT_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

void ParentRoutine(const char* pathToChild, FILE* input);

#endif