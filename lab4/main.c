#include "interp.h"
#include <math.h>
#include <stdio.h>

#define PI 3.141592653589793

static double f (double x) {
  double m = 0.0;
  double s = 0.5;
  double e = (x-m)/s;
  return exp(-0.5 * e * e) / (s * sqrt(2.0 * PI));
}

#define N 10
int main (void)
{
  double xi[N];
  double bi[N];
  
  printf("Amostragem regular [-2, 2]\n");
  for (int i = 2; i <= N; i++) {
    // calcular i amostras regulares
    regular(i, -2.0, 2.0, xi);
    printf("%d: ", i);
    for (int j = 0; j < i; j++)
      printf("%.6f ", xi[j]);
    printf("\n");
  } 

  printf("\nCoeficientes usando amostras regulares\n");
  // calcular 10 amostras regulares [-2, 2]
  regular(N, -2.0, 2.0, xi);
  // calcular 'coeficientes' com as amostras regulares
  coeficientes(N, xi, f, bi);
  for (int i=0; i < N; ++i)
    printf("%g ", bi[i]);
  printf("\n");

  printf("\nAvalia com coeficientes de amostras regulares\n");
  for (float x=-2.0; x < 2.0001; x+=0.1) {
    double y = avalia(N, xi, bi, x); // chamar 'avalia' passando valores de xi, bi e x
    double yf = f(x);
    printf("x: %.1f y: %f f(x): %f (y-f(x)): %g\n",x,y,yf,fabs(y-yf));
  }

  printf("\nAmostragem chebyshev [-2, 2]\n");
  for (int i = 2; i <= N; i++) {
    // calcular amostras chebyshev
    chebyshev(i, -2.0, 2.0, xi);
    printf("%d: ", i);
    for (int j = 0; j < i; j++)
      printf("%.6f ", xi[j]);
    printf("\n");
  } 
  
  printf("\nCoeficientes usando amostras chebyshev\n");
  // calcular 10 amostras chebyshev [-2, 2]
  chebyshev(N, -2.0, 2.0, xi);
  // calcular 'coeficientes' com as amostras chebyshev
  coeficientes(N, xi, f, bi);
  for (int i=0; i < N; ++i)
    printf("%g ", bi[i]);
  printf("\n");

  printf("\nAvalia com coeficientes de amostras chebyshev\n");
  for (float x=-2.0; x < 2.0001; x+=0.1) {
    double y = avalia(N, xi, bi, x); // chamar 'avalia' passando valores de xi, bi e x
    double yf = f(x);
    printf("x: %.1f y: %f f(x): %f (y-f(x)): %g\n",x,y,yf,fabs(y-yf));
  }
  
  return 0;
}
