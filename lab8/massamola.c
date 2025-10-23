#include "massamola.h"
#include <math.h>

void forca (double t, double x, double y, double* fx, double* fy)
{
  // Parâmetros
  const double k = 0.3;
  const double r = 200.0;
  const double m = 2.0;
  const double g = 9.8;
  const double w = 10.0;
  
  // Força de gravidade: fg = mg = [0, mg]
  double fgx = 0.0;
  double fgy = m * g;
  
  // Força de vento: fw = w * e^(-t/20) = [w*e^(-t/20), 0]
  double fwx = w * exp(-t / 20.0);
  double fwy = 0.0;
  
  // Força de mola: fk = -k(||p|| - r) * p/||p||
  double norm_p = sqrt(x * x + y * y);
  double fkx = 0.0;
  double fky = 0.0;
  
  if (norm_p > 0) {
    fkx = -k * (norm_p - r) * (x / norm_p);
    fky = -k * (norm_p - r) * (y / norm_p);
  }
  
  // Força total
  *fx = fgx + fwx + fkx;
  *fy = fgy + fwy + fky;
}

double evolui (double t, double h, double x, double y, double xp, double yp, double* xn, double* yn)
{
  // Parâmetros
  const double delta = 0.002;
  const double m = 2.0;
  
  // Calcular força no instante atual
  double fx, fy;
  forca(t, x, y, &fx, &fy);
  
  // Método de Verlet com amortecimento:
  // p_{i+1} = p_i + (1 - delta)(p_i - p_{i-1}) + h^2 * f_i / m
  *xn = x + (1.0 - delta) * (x - xp) + h * h * fx / m;
  *yn = y + (1.0 - delta) * (y - yp) + h * h * fy / m;
  
  // Retornar tempo atualizado
  return t + h;
}

void simula (double x0, double y0, double t_final, int n, double* x, double* y)
{
  // Passo de integração
  double h = t_final / n;
  
  // Condições iniciais: velocidade nula, então p_{-1} = p_0
  double xp = x0;
  double yp = y0;
  double xc = x0;
  double yc = y0;
  double t = 0.0;
  
  // Simular n passos
  for (int i = 0; i < n; i++) {
    double xn, yn;
    t = evolui(t, h, xc, yc, xp, yp, &xn, &yn);
    
    // Salvar posição
    x[i] = xn;
    y[i] = yn;
    
    // Atualizar para próxima iteração
    xp = xc;
    yp = yc;
    xc = xn;
    yc = yn;
  }
}