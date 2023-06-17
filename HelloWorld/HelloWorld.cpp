#include <stdio.h>
#include <math.h>

double root(double x)
{
    return sqrt(x);
}

int square(int x)
{
    return x * x;
}

int main(int argc, char* argv[])
{
    int x = 42;
    double y = 56.8;

    printf("\nHello, World!");

    printf("\nThe square of %d is %d", x, square(x));
    printf("\nThe square root of %lf is %lf", y, root(y));

    return 0;
}