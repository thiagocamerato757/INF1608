#include "gradconj.h"
#include "matriz.h"
#include "vetor.h"
#include <stdlib.h>
#include <stdio.h>

static void print_solution (int n, double* v)
{
  for (int i=0; i<n; ++i)
    printf("%.8f  ",v[i]);
  printf("\n");
}

static void print_system (int n, double** A, double* v)
{
  for (int i=0; i<n; ++i) {
    for (int j=0; j<n; ++j)
      printf("%4.2g ",A[i][j]);
    printf("| %4.2g \n", v[i]);
  }
}

#define GRAD_CONJ_TOL 1e-7
static void grad_conj_test (int n, double** A, double* b)
{
  int it = 0;
  double* x = (double *) malloc(sizeof(double) * n);

  print_system(n, A, b);
  
  for (int i=0; i<n; ++i) x[i] = 0.0;
  it = gradconj(n, A, b, x, GRAD_CONJ_TOL);
  printf("GC iter: %d\n", it);
  print_solution(n, x);

  for (int i=0; i<n; ++i) x[i] = 0.0;
  it = gradconj_jacobi(n, A, b, x, GRAD_CONJ_TOL);
  printf("GCJC iter: %d\n", it);
  print_solution(n, x);
  
  printf("----------------\n");

  free(x);
}

int main (void)
{
  {
    int n = 2;
    double** A = mat_cria(n,n);
    A[0][0] = 3; A[0][1] = 2;
    A[1][0] = 2; A[1][1] = 6;
    double b[] = { 2, -8 };

    grad_conj_test(n, A, b);

    mat_libera(n, A);
  }
  {
    int n = 2;
    double** A = mat_cria(n,n);
    A[0][0] = 2; A[0][1] = 1;
    A[1][0] = 1; A[1][1] = 2;
    double b[] = { 10, 8 };

    grad_conj_test(n, A, b);

    mat_libera(n, A);
  }
  {
    int n = 2;
    double** A = mat_cria(n,n);
    A[0][0] = 3; A[0][1] = 1;
    A[1][0] = 1; A[1][1] = 2;
    double b[] = { 5, 5 };

    grad_conj_test(n, A, b);

    mat_libera(n, A);
  }
  {
    int n = 3;
    double** A = mat_cria(n,n);
    A[0][0] = 4; A[0][1] = 1;  A[0][2] = 1;
    A[1][0] = 1; A[1][1] = 3;  A[1][2] = 0;
    A[2][0] = 1; A[2][1] = 0;  A[2][2] = 2;
    double b[] = { 9,7,7};

    grad_conj_test(n, A, b);

    mat_libera(n, A);
  }
  {
    int n = 4;
    double** A = mat_cria(n,n);
    A[0][0] = 6; A[0][1] = 2;  A[0][2] = 1;  A[0][3] = 0;
    A[1][0] = 2; A[1][1] = 5;  A[1][2] = 2;  A[1][3] = 1;
    A[2][0] = 1; A[2][1] = 2;  A[2][2] = 4;  A[2][3] = 1;
    A[3][0] = 0; A[3][1] = 1;  A[3][2] = 1;  A[3][3] = 3;
    double b[] = {9, 10, 8, 5};

    grad_conj_test(n, A, b);

    mat_libera(n, A);
  }
  {
    int n = 6;
    double** A = mat_cria(n,n);
    for (int i=0; i<n; ++i) {
      for (int j=0; j<n; ++j) {
        if (i==j) 
          A[i][j] = 3.0;
        else if (i+j == n-1)
          A[i][j] = 0.5;
        else
          A[i][j] = 0.0;
      }
    }
    for (int i=0; i<n-1; ++i) {
      A[i][i+1] = -1;
    }
    for (int i=1; i<n; ++i) {
      A[i][i-1] = -1;
    }
    A[0][n-1] = 0.5;
    A[n-1][0] = 0.5;

    double* b = (double*)malloc(sizeof(double) * n);
    b[1] = b[4] = 1.5;
    for (int i=0; i<n; ++i) {
      if (i == 0 || i == n-1)
        b[i] = 2.5;
      else if (i == n / 2 || (n % 2 == 0 && i == (n - 1) / 2))
        b[i] = 1.0;
      else 
        b[i] = 1.5;
    }

    grad_conj_test(n, A, b);

    free(b);
    mat_libera(n, A);
  }
  {
    int n = 10;
    double** A = mat_cria(n,n);
    for (int i=0; i < n; ++i)
      for (int j=0; j < n; ++j)
        A[i][j] = 0.0;
    for (int i=0; i<n; ++i)
      A[i][i] = i+1;
    for (int i=0; i<n-1; ++i)
      A[i][i+1] = A[i+1][i] = 0.4;

    double* b = (double*)malloc(sizeof(double) * n);
    double* x = (double*)malloc(sizeof(double) * n);

    for (int i=0; i<n; ++i)
      x[i] = 1;
    mat_multv(n,n,A,x,b);

    grad_conj_test(n, A, b);

    free(b);
    free(x);
    mat_libera(n, A);
  }
  return 0;
}