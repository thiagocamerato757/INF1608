#include "ode.h"
#include <stdio.h>
#include <math.h>

static double c = 10.0;

static int N;
static double fa (double t, double y)
{
  N++;
  return c*y*(1.0-y);
}

// Resultado de fa considerando y(0) = 0.5
static double Sfa (double t)
{
  return 1.0 / (1.0 + exp(-c * t));
}

static double fn (double t, double y)
{
  N++;
  return t*y + t*t*t;
}

// Resultado de fn considerando y(0) = -1
static double Sfn (double t)
{
  return exp(t*t/2.0) - t*t - 2.0;
}

void teste_runge_kutta (double t0, double t1, double h, double y0,
                        double (*f) (double t, double y), 
                        double (*Sf) (double t))
{
  printf("Solucao em %g: %g\n", t1, Sf(t1));
  N = 0;
  double p = RungeKuttaPasso(t0, h, y0, f);
  printf("RungeKuttaPasso: N=%d rk=%.16lf diff=%g\n",N,p,fabs(Sf(t0+h)-p));
  N = 0;
  int n = (int)((t1 - t0) / h);
  double e = RungeKutta(t0, t1, n, y0, f);
  printf("RungeKutta: N=%d rk=%.16lf diff=%g\n",N,e,fabs(Sf(t1)-e));
  N = 0;
  double g = RungeKuttaAdaptativo(t0, t1, y0, f, 1e-12);
  printf("RungeKuttaAdaptativo: N=%d rk=%.16lf diff=%g\n",N,g,fabs(Sf(t1)-g));
}

int main (void)
{
  printf("--- Teste de Runge-Kutta (a) ---\n");
  teste_runge_kutta(0, 2.0, 0.01, 0.5, fa, Sfa);
  printf("--- Teste de Runge-Kutta (b) ---\n");
  teste_runge_kutta(0, 2.4, 0.001, -1, fn, Sfn);
  return 0;
}
