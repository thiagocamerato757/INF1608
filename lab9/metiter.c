/*
 * metiter.c
 * Implementação de métodos iterativos para sistemas lineares
 * INF1608 - Análise Numérica
 */

#include "metiter.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Calcula a norma-2 (euclidiana) de um vetor
 * 
 * @param n  Dimensão do vetor
 * @param v  Vetor de entrada
 * @return   Norma-2 do vetor: sqrt(v[0]² + v[1]² + ... + v[n-1]²)
 */
static double norm2(int n, double* v) {
  double sum = 0.0;
  for (int i = 0; i < n; i++) {
    sum += v[i] * v[i];
  }
  return sqrt(sum);
}

/**
 * Calcula o vetor resíduo r = b - Ax de um sistema linear
 * 
 * @param n  Dimensão do sistema
 * @param A  Matriz de coeficientes
 * @param b  Vetor independente
 * @param x  Vetor solução atual
 * @param r  Vetor resíduo (saída)
 */
static void compute_residual(int n, double** A, double* b, double* x, double* r) {
  for (int i = 0; i < n; i++) {
    r[i] = b[i];
    for (int j = 0; j < n; j++) {
      r[i] -= A[i][j] * x[j];
    }
  }
}

/**
 * Implementação do método iterativo de Gauss-Seidel
 * 
 * Itera atualizando cada componente da solução pela fórmula:
 *   x[i] = (b[i] - Σ(A[i][j] * x[j])) / A[i][i]  para j ≠ i
 * 
 * A atualização é feita in-place, usando os valores mais recentes de x.
 * O critério de parada é ||r||₂ ≤ tol, onde r = b - Ax é o resíduo.
 */
int gaussseidel (int n, double** A, double* b, double* x, double tol)
{
  int iter = 0;
  double* r = (double*)malloc(sizeof(double) * n);
  
  while (1) {
    iter++;
    
    // Atualiza cada componente da solução
    for (int i = 0; i < n; i++) {
      double sum = b[i];
      for (int j = 0; j < n; j++) {
        if (j != i) {
          sum -= A[i][j] * x[j];
        }
      }
      x[i] = sum / A[i][i];
    }
    
    // Verifica critério de parada
    compute_residual(n, A, b, x, r);
    double norm_r = norm2(n, r);
    
    if (norm_r <= tol) {
      break;
    }
  }
  
  free(r);
  return iter;
}

/**
 * Implementação do método Gauss-Seidel com sobre-relaxamento (SOR)
 * 
 * Combina Gauss-Seidel com um fator de relaxamento w para acelerar a convergência:
 *   1. Calcula x_gs[i] pelo método de Gauss-Seidel padrão
 *   2. Aplica relaxamento: x[i] = (1-w) * x_old[i] + w * x_gs[i]
 * 
 * Para w > 1.0, temos sobre-relaxamento que acelera a convergência.
 * O critério de parada é ||r||₂ ≤ tol, onde r = b - Ax é o resíduo.
 */
int sor_gaussseidel (int n, double** A, double* b, double* x, double tol, double w)
{
  int iter = 0;
  double* r = (double*)malloc(sizeof(double) * n);
  
  while (1) {
    iter++;
    
    // Atualiza cada componente com relaxamento
    for (int i = 0; i < n; i++) {
      double x_old = x[i];
      
      // Calcula valor pelo método de Gauss-Seidel
      double sum = b[i];
      for (int j = 0; j < n; j++) {
        if (j != i) {
          sum -= A[i][j] * x[j];
        }
      }
      double x_gs = sum / A[i][i];
      
      // Aplica relaxamento
      x[i] = (1.0 - w) * x_old + w * x_gs;
    }
    
    // Verifica critério de parada
    compute_residual(n, A, b, x, r);
    double norm_r = norm2(n, r);
    
    if (norm_r <= tol) {
      break;
    }
  }
  
  free(r);
  return iter;
}