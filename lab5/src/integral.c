#include <stdio.h>
#include <math.h>

double IntegrateRectangles(double a, double b, double epsilon)
{
    int steps = fabs(b - a) / epsilon;
    double point = a;
    double result = 0;

    for (int i = 0; i < steps; ++i)
    {
        result += sin(point) * epsilon;
        point += epsilon;
    }
    
    return result;
}

double IntegrateTrapezoids(double a, double b, double epsilon)
{
    int steps = fabs(b - a) / epsilon;
    double point = a;
    double result = 0;

    for (int i = 0; i < steps; ++i)
    {
        result += sin(point + epsilon / 2) * epsilon;
        point += epsilon;
    }

    return result;
}

int main(void)
{
    printf("%f\n", IntegrateTrapezoids(0, 1, 0.1));
    printf("%f\n", IntegrateRectangles(0, 1, 0.1));
    
    return 0;
}

