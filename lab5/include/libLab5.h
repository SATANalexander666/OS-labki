typedef double(*TDerivative)(double, double);        
typedef double(*TIntegral)(double, double, double);

double Derivative(double a, double deltaX);
double Integrate(double a, double b, double epsilon);
