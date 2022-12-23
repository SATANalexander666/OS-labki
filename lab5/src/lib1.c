#include <math.h>

double Derivative(double a, double deltaX){
    return (cos(a + deltaX) - cos(a)) / deltaX;
}

double Integrate(double a, double b, double epsilon)
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
