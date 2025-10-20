#ifndef ODE_H
#define ODE_H

double RungeKuttaPasso (double t, double h, double y, double (*f) (double t, double y));
double RungeKutta (double t0, double t1, int n, double y0, double (*f) (double t, double y));
double RungeKuttaAdaptativo (double t0, double t1, double y0, double (*f) (double t, double y), double tol);

#endif