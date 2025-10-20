#include "ode.h"
#include <math.h>

double RungeKuttaPasso (double t, double h, double y, double (*f) (double t, double y))
{
  double k1 = h * f(t, y);
  double k2 = h * f(t + h/2.0, y + k1/2.0);
  double k3 = h * f(t + h/2.0, y + k2/2.0);
  double k4 = h * f(t + h, y + k3);
  
  return y + (k1 + 2.0*k2 + 2.0*k3 + k4) / 6.0;
}

double RungeKutta (double t0, double t1, int n, double y0, double (*f) (double t, double y))
{
  double h = (t1 - t0) / n;
  double t = t0;
  double y = y0;
  
  for (int i = 0; i < n; i++) {
    y = RungeKuttaPasso(t, h, y, f);
    t += h;
  }
  
  return y;
}

double RungeKuttaAdaptativo (double t0, double t1, double y0, double (*f) (double t, double y), double tol)
{
  double h = 1.0e-7;
  double t = t0;
  double y = y0;
  
  while (t < t1) {
    // Ajusta h se formos ultrapassar t1
    if (t + h > t1) {
      h = t1 - t;
    }
    
    // Um passo com h
    double y1 = RungeKuttaPasso(t, h, y, f);
    
    // Dois passos com h/2
    double y_temp = RungeKuttaPasso(t, h/2.0, y, f);
    double y2 = RungeKuttaPasso(t + h/2.0, h/2.0, y_temp, f);
    
    // Estima o erro
    double delta = (y2 - y1) / 15.0;
    
    // Calcula o fator de escala
    double f_factor = pow(tol / fabs(delta), 0.2);
    
    if (f_factor >= 1.0) {
      // Aceita o passo
      y = y2 + delta;
      t += h;
      
      // Atualiza h para próxima iteração
      if (f_factor > 1.2) {
        h = 1.2 * h;
      } else {
        h = f_factor * h;
      }
    } else {
      // Rejeita o passo e tenta novamente com h menor
      h = 0.8 * f_factor * h;
    }
  }
  
  return y;
}