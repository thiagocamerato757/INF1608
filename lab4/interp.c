#include "interp.h"
#include <math.h>
#include <stdlib.h>

#ifndef PI
#define PI 3.141592653589793
#endif

void regular(int n, double a, double b, double* xi) {
    // Generate n regular samples in the interval [a, b]
    if (n > 1) {
        double step = (b - a) / (n - 1);
        for (int i = 0; i < n; i++) {
            xi[i] = a + i * step;
        }
    }
    else {
        xi[0] = a;
    }
}

void chebyshev(int n, double a, double b, double* xi) {
    // Generate n Chebyshev samples in the interval [a, b]
    double center = (a + b) / 2.0;
    double radius = (b - a) / 2.0;
    
    for (int i = 0; i < n; i++) {
        // Chebyshev nodes: cos((2i+1)π/(2n)) for i=0..n-1
        double theta = (2.0 * i + 1.0) * PI / (2.0 * n);
        xi[i] = center + radius * cos(theta);
    }
}

void coeficientes(int n, double* xi, double (*f)(double), double* bi) {
    for (int i = 0; i < n; i++) {
        bi[i] = f(xi[i]);
    }

    for (int j = 1; j < n; j++) {
        for (int i = n - 1; i >= j; i--) {
            bi[i] = (bi[i] - bi[i-1]) / (xi[i] - xi[i-j]);
        }
    }
}

double avalia(int n, double* xi, double* bi, double x) {
    double result = bi[n-1];
    for (int i = n - 2; i >= 0; i--) {
        result = result * (x - xi[i]) + bi[i];
    }
    return result;
}