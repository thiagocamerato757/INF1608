#include "matriz.h"
#include "sistlinear.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
void gauss (int n, double** a, double* b, double* x)
{
  for (int j=0; j<n-1; ++j) {
    // find pivô
    int m = j;
    for (int i=j+1; i<n; ++i)
      if (fabs(a[i][j]) > fabs(a[m][j]))
        m = i;
    // swap lines: j <-> m
    double t;
    for (int k=j; k<n; ++k) {
      t = a[j][k];
      a[j][k] = a[m][k];
      a[m][k] = t;
    }
    t = b[j];
    b[j] = b[m];
    b[m] = t;

    // elimination
    for (int i=j+1; i<n; ++i) {
      double f = a[i][j]/a[j][j];
      for (int k=j; k<n; ++k)
        a[i][k] -= f*a[j][k];
      b[i] -= f*b[j];
    }
  }
  // backward substitution
  for (int i=n-1; i>=0; --i) {
    double s = 0;
    for (int j=i+1; j<n; ++j) 
      s += a[i][j]*x[j];
    x[i] = (b[i] - s) / a[i][i];
  }
}