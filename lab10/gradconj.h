#ifndef GRAD_CONJ_H
#define GRAD_CONJ_H

int gradconj (int n, double** A, double* b, double* x, double tol);
int gradconj_jacobi (int n, double** A, double* b, double* x, double tol);

#endif