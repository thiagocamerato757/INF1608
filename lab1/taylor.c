#include "taylor.h"
#include <stdlib.h>

double avalia_taylor (int n, double *c, double x0, double x) {
  // Calcula (x - x0) uma única vez
  double dx = x - x0;
  
  // Inicializa as variáveis para o cálculo eficiente
  double resultado = 0.0;
  double potencia_dx = 1.0;  // (x - x0)^i
  double fatorial = 1.0;     // i!
  
  // Avalia o polinômio de Taylor usando a fatoração natural dos termos
  // Termo 0: c[0] * (x - x0)^0 / 0! = c[0]
  resultado = c[0];
  
  // Para os termos subsequentes, usamos a relação de recorrência:
  // (x - x0)^i = (x - x0)^(i-1) * (x - x0)
  // i! = (i-1)! * i
  for (int i = 1; i < n; i++) {
    potencia_dx *= dx;        // (x - x0)^i
    fatorial *= i;            // i!
    resultado += c[i] * potencia_dx / fatorial;
  }
  
  return resultado;
}

double avalia_seno (int n, double x) {
  // Vetor estático para os coeficientes - evita alocação dinâmica
  // Usamos um tamanho máximo razoável para acomodar a maioria dos casos
  static double c[50];


  // Preenche o vetor de coeficientes seguindo o padrão:
  // 0, 1, 0, -1, 0, 1, 0, -1, ...
  // que corresponde aos coeficientes da série de Taylor de sin(x) em torno de x0=0
  for (int i = 0; i < 50; i++) {
    switch (i % 4) {
      case 0: 
        c[i] = 0.0;
        break;
      case 1: 
        c[i] = 1.0;
        break;
      case 2: 
        c[i] = 0.0;
        break;
      case 3: 
        c[i] = -1.0;
        break;
    }
  }
  
  // Avalia o polinômio de Taylor em torno de x0 = 0
  double resultado = avalia_taylor(n, c, 0.0, x);
  
  return resultado;
}