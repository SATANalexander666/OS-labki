#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "libLab5.h"

int main()
{
    char* libNames[] = {"./libdynamic1.so", "./libdynamic2.so"};
    int curLib = 0;
    int numOfLibs = 2;

    void* libCtrl;
    libCtrl  = dlopen(libNames[curLib], RTLD_NOW);
    
    if (!libCtrl)
    {
        perror("Openning dynamic lib error )");
        exit(EXIT_FAILURE);
    }

    TDerivative derivative;
    TIntegral integral;

    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wpedantic"
        derivative = (TDerivative)dlsym(libCtrl, "Derivative"); 
        integral = (TIntegral)dlsym(libCtrl, "Integrate");
    #pragma GCC diagnostic pop

    printf("0 - switch library (default - derivative), 1 - find derivative, 2 - integrate\n");

    int command;

    while(scanf("%d", &command) != EOF)
    {  
        if (command == 0)
        {
            curLib = (curLib + 1) % numOfLibs;

            if (dlclose(libCtrl ) != 0)
            {
                perror("closing dynamic lib error");
                exit(EXIT_FAILURE);
            }

            if (!(libCtrl = dlopen(libNames[curLib], RTLD_LAZY)))
            {
                perror("closing dynamic lib error");
                exit(EXIT_FAILURE);
            }

            #pragma GCC diagnostic push
            #pragma GCC diagnostic ignored "-Wpedantic"
                derivative = (TDerivative)dlsym(libCtrl, "Derivative"); 
                integral = (TIntegral)dlsym(libCtrl, "Integrate");
            #pragma GCC diagnostic pop
        }
        else if (command == 1)
        {
            printf("Pass arguments: \"a deltaX\"\n");

            double a, deltaX;
            scanf("%lf %lf", &a, &deltaX);

            double result = (derivative)(a, deltaX);
            printf("%lf\n", result);
        }
        else if (command == 2)
        {
            printf("Pass arguments: \"a b epsilon\"\n");

            double a, b, epsilon;
            scanf("%lf %lf %lf", &a, &b, &epsilon);

            double result = (integral)(a, b, epsilon);
            printf("%lf\n", result);
        }
        else if (command == -1){
            break;
        }
        else{
            return 0;
        }
    }

    return 0;
}







