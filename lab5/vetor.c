#include "vetor.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double* vet_cria (int n)
{
  double* v = (double*)malloc(n*sizeof(double));
  return v;
}
void vet_libera (double* v)
{
  free(v);
}
double vet_escalar (int n, double* v, double* w)
{
  double s = 0;
  for (int i=0; i<n; ++i)
    s += v[i]*w[i];
  return s;
}
double vet_norma2 (int n, double* v)
{
  double s = vet_escalar(n,v,v);
  return sqrt(s);
}

int vet_iguais (int n, double* g, double* x, double tol)
{
  for (int i=0; i<n; ++i) {
    if (fabs(g[i]-x[i]) > tol)
      return 0;
  }
  return 1;
}

void vet_mults (int n, double* v, double s, double* w)
{
  for (int i=0; i<n; ++i)
    w[i] = v[i]*s;
}

void vet_imprime (int n, double* v)
{
  for (int i=0; i<n; ++i)
    printf("%.16g  ",v[i]);
  printf("\n");
}

