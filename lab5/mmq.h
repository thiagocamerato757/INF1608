#ifndef MMQ_H
#define MMQ_H

double mmq (int m, int n, double** A, double* b, double* x);
double ajuste_parabola (int n, double* px, double* py, double* a, double* b, double* c);
double ajuste_cubica (int n, double* px, double* py, double* a, double* b, double* c, double* d);
double ajuste_exponencial_exp (int n, double* px, double* py, double* a, double* b);

#endif