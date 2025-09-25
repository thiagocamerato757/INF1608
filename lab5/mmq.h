
#ifndef MMQ_H
#define MMQ_H

// calcula a solucao de quadrados minimos para o sistema Ax=b
// retorna o erro quadratico
double mmq (int m, int n, double** A, double* b, double* x);

// calcula o ajuste de uma parabola para um conjunto de pontos
// retorna o erro quadratico
double ajuste_parabola (int n, double* px, double* py, double* a, double* b, double* c);

// calcula o ajuste de uma cubica para um conjunto de pontos
// retorna o erro quadratico
double ajuste_cubica (int n, double* px, double* py, double* a, double* b, double* c, double* d);

// calcula o ajuste exponencial da forma y = a*exp(b*x) para um conjunto de pontos
// retorna o erro quadratico no sistema linearizado
double ajuste_exponencial (int n, double* px, double* py, double* a, double* b);

#endif
