#ifndef OTIMIZACAO_H
#define OTIMIZACAO_H

int msa (double a, double b, double (*f) (double x), double tol, double *xmin);
int mips (double r, double delta, double (*f) (double x), double tol, double *xmin);

#endif