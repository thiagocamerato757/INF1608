#ifndef RUNGE_KUTTA_H
#define RUNGE_KUTTA_H

typedef struct {
    double theta;  // ângulo (radianos)
    double omega;  // velocidade angular (rad/s)
} PenduloEstado;

typedef struct {
    double g;      // aceleração da gravidade (m/s²)
    double L;      // comprimento do pêndulo (m)
} PenduloParametros;

// Função para calcular a derivada do sistema
void pendulo_derivada(double t, PenduloEstado *estado, PenduloEstado *derivada, PenduloParametros *params);

// Método de Runge-Kutta de 4ª ordem
void rk4_passo(double t, PenduloEstado *estado, double dt, PenduloParametros *params);

// Resolve o sistema usando RK4 para múltiplos passos
void rk4_resolver(PenduloEstado *estado_inicial, double t0, double tf, int n_passos, 
                  PenduloParametros *params, PenduloEstado *solucao, double *tempo);

#endif
