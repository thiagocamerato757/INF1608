#ifndef DERIVADA_INTEGRAL_H
#define DERIVADA_INTEGRAL_H

double derivada (double (*f) (double x), double x, double h);
double simpson (double (*f) (double), double a, double b, int n);
double simpsonadaptativo (double (*f) (double), double a, double b, double tol);

#endif