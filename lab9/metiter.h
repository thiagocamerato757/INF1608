/*
 * metiter.h
 * Módulo para métodos iterativos de resolução de sistemas lineares
 * INF1608 - Análise Numérica
 */

#ifndef GAUSS_SEIDEL_H
#define GAUSS_SEIDEL_H

/**
 * Resolve um sistema linear Ax = b usando o método de Gauss-Seidel
 * 
 * @param n     Dimensão do sistema (matriz n×n)
 * @param A     Matriz de coeficientes (estritamente diagonal dominante)
 * @param b     Vetor independente
 * @param x     Vetor solução (entrada: aproximação inicial, saída: solução final)
 * @param tol   Tolerância para o critério de parada (norma-2 do resíduo)
 * @return      Número de iterações realizadas
 */
int gaussseidel (int n, double** A, double* b, double* x, double tol);

/**
 * Resolve um sistema linear Ax = b usando Gauss-Seidel com sobre-relaxamento (SOR)
 * 
 * @param n     Dimensão do sistema (matriz n×n)
 * @param A     Matriz de coeficientes (estritamente diagonal dominante)
 * @param b     Vetor independente
 * @param x     Vetor solução (entrada: aproximação inicial, saída: solução final)
 * @param tol   Tolerância para o critério de parada (norma-2 do resíduo)
 * @param w     Fator de relaxamento (w > 1.0 para sobre-relaxamento)
 * @return      Número de iterações realizadas
 */
int sor_gaussseidel (int n, double** A, double* b, double* x, double tol, double w);

#endif