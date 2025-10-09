#include "derivadaintegral.h"

#include <stdio.h>
#include <math.h>

#define PI 3.141592653589793

void teste_derivada (double (*f) (double), double (*fl) (double), double x)
{
  for (int i=1; i < 13; ++i) {
    double h = pow(10,-i);
    double d = derivada(f, x, h); // COMPLETAR: calcular derivada
    double a = fl(x);
    printf("%e  %.16g  %.16g\n",h,d,fabs(d-a));
  }
}

void teste_simpson (double (*f) (double), double a, double b)
{
  double s16 = simpson(f, a, b, 16); // COMPLETAR: chamar simpson com 16 passos
  double s32 = simpson(f, a, b, 32); // COMPLETAR: chamar simpson com 32 passos
  printf("%.16g  %.16g\n",s16,s32);
}

void teste_adaptativo (double (*f) (double), double a, double b, double d)
{
  for (int i = 1; i < 13; ++i) {
    double tol = pow(10,-i);
    double s = simpsonadaptativo(f, a, b, tol); // COMPLETAR: chamar simpson adaptativo em [a,b]
    printf("%e %.16g %e\n", tol, s, fabs(d-s));
  }
}

static double fd1 (double x) {
  return cos(x) - 2*sin(x);
}
static double fd1l (double x) {
  return -sin(x) - 2*cos(x);
}
static double fd2 (double x) {
  return exp(x);
}
static double fd2l (double x) {
  return exp(x);
}
static double fi1 (double x) {
  return x / sqrt(x*x+9);
}
static double fi2 (double x) {
  return x*x*sin(x);
}
static double fi3 (double x) {
  return (2/sqrt(PI)) * exp(-(x*x));
}
static double fi4 (double x) {
  return log(cos(x) + sin(x));
}

int main (void)
{
  printf("f1: cos(x) - 2*sin(x) | f1l: -sin(x) - 2*cos(x)\n");
  teste_derivada(fd1, fd1l, 0.0);
  printf("f2: exp(x) | f2l: exp(x)\n");
  teste_derivada(fd2, fd2l, 0.0);
  printf("-----------------------------\n");
  printf("f1: x / sqrt(x*x+9)\n");
  teste_simpson(fi1, 0, 4);
  printf("f2: x*x*sin(x)\n");
  teste_simpson(fi2, 0, PI);
  printf("f3: (2/sqrt(PI)) * exp(-(x*x))\n");
  teste_simpson(fi3, 0, 3);
  printf("f4: ln(cos(x) + sin(x))\n");
  teste_simpson(fi4, 0, PI/2);
  printf("-----------------------------\n");
  printf("f1: x / sqrt(x*x+9)\n");
  teste_adaptativo(fi1, 0, 4, 2.0);
  printf("f2: x*x*sin(x)\n");
  teste_adaptativo(fi2, 0, PI, 5.8696044010894);
  printf("f3: (2/sqrt(PI)) * exp(-(x*x))\n");
  teste_adaptativo(fi3, 0, 3, 0.9999779095030014);
  printf("f4: ln(cos(x) + sin(x))\n");
  teste_adaptativo(fi4, 0, PI/2, 0.3715690716013184);
  return 0;
}