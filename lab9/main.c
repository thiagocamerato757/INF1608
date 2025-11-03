/*
 * main.c
 * Programa de teste para métodos iterativos de resolução de sistemas lineares
 * INF1608 - Análise Numérica
 * 
 * Testa os métodos de Gauss-Seidel e Gauss-Seidel com SOR em três sistemas:
 * 1. Sistema 2×2 com solução [1, 2]
 * 2. Sistema 3×3 com solução [2, -1, 1]
 * 3. Sistema 6×6 com solução [1, 1, 1, 1, 1, 1]
 */

#include "metiter.h"
#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>

#define TOL 1e-7  // Tolerância de convergência

/**
 * Testa os dois métodos iterativos para um sistema linear Ax = b
 * Exibe o número de iterações e a solução encontrada por cada método
 * 
 * @param n  Dimensão do sistema
 * @param A  Matriz de coeficientes
 * @param b  Vetor independente
 */
void testa_lab (int n, double** A, double* b)
{
  double* x = (double*)malloc(sizeof(double)*n);

  // Gauss Seidel:
  for (int i=0; i<n; ++i)
    x[i] = 0.0;
  int it = gaussseidel(n, A, b, x, TOL);
  printf("iter: %d\n", it);
  for (int i=0; i<n; ++i)
    printf("%.7f\n", x[i]);
  
  // Gauss Seidel + SOR:
  for (int i=0; i<n; ++i)
    x[i] = 0.0;
  it = sor_gaussseidel(n, A, b, x, TOL, 1.1);
  printf("iter: %d\n",it);
  for (int i=0; i<n; ++i)
    printf("%.7f\n", x[i]);    

  // liberando memoria utilizada
  free(x);
}

int main (void)
{
  // Teste 1: Sistema 2×2
  // [ 3  1 ] [ x1 ]   [ 5 ]
  // [ 1  2 ] [ x2 ] = [ 5 ]
  // Solução esperada: x = [1, 2]
  {
    int n = 2;
    double** A = mat_cria(n,n);
    A[0][0] = 3; A[0][1] = 1;
    A[1][0] = 1; A[1][1] = 2;
    double b[] = {5,5};

    testa_lab(n, A, b);

    mat_libera(n, A);
  }

  // Teste 2: Sistema 3×3
  // [ 3  1 -1 ] [ x1 ]   [ 4 ]
  // [ 2  4  1 ] [ x2 ] = [ 1 ]
  // [-1  2  5 ] [ x3 ]   [ 1 ]
  // Solução esperada: x = [2, -1, 1]
  {
    int n = 3;
    double** A = mat_cria(n,n);
    A[0][0] = 3; A[0][1] = 1;  A[0][2] =-1;
    A[1][0] = 2; A[1][1] = 4;  A[1][2] = 1;
    A[2][0] =-1; A[2][1] = 2;  A[2][2] = 5;
    double b[] = {4,1,1};

    testa_lab(n, A, b);

    mat_libera(n, A);
  }

  // Teste 3: Sistema 6×6 (matriz tridiagonal com elementos na anti-diagonal)
  // Solução esperada: x = [1, 1, 1, 1, 1, 1]
  {
    int n = 6;
    double** A = mat_cria(n,n);
    
    // Inicializa matriz com zeros
    for (int i=0; i<n; ++i) {
      for (int j=0; j<n; ++j) {
        if (i==j) 
          A[i][j] = 3.0;           // Diagonal principal
        else if (i+j == n-1)
          A[i][j] = 0.5;           // Anti-diagonal
        else
          A[i][j] = 0.0;
      }
    }
    
    // Diagonal superior
    for (int i=0; i<n-1; ++i) {
      A[i][i+1] = -1;
    }
    
    // Diagonal inferior
    for (int i=1; i<n; ++i) {
      A[i][i-1] = -1;
    }
    
    A[0][n-1] = 0.5;
    A[n-1][0] = 0.5;

    double b[6];
    b[0] = b[5] = 2.5;
    b[1] = b[4] = 1.5;
    for (int i=2; i<n-2; ++i)
      b[i] = 1.0;

    testa_lab(n, A, b);

    mat_libera(n, A);
  }

  return 0;
}
