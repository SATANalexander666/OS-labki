#include <stdio.h>
#include <libLab5.h>

int main()
{
    printf("1 - integrate, 2 - find derivative, -1 - quit\n");

    int command;

    while (scanf("%d", &command) != EOF)
    {
        if (command == 1)
        {
            printf("Pass arguments: \"a b epsilon\"\n");

            double a, b, epsilon;
            scanf("%lf %lf %lf", &a, &b, &epsilon);

            printf("%lf\n", Integrate(a, b, epsilon));
        }
        else if (command == 2)
        {
            printf("Pass arguments: \"a deltaX\"\n");

            double a, deltaX;
            scanf("%lf %lf", &a, &deltaX);

            printf("%lf\n", Derivative(a, deltaX));
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
