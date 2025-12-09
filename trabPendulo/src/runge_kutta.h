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

typedef struct {
    int n_passos;
    double tempo_total;
    double periodo;
} ResultadoSimulacao;

// Função para calcular a derivada do sistema
void pendulo_derivada(double t, PenduloEstado *estado, PenduloEstado *derivada, PenduloParametros *params);

// Método de Runge-Kutta de 4ª ordem - um passo
void rk4_passo(double t, PenduloEstado *estado, double dt, PenduloParametros *params);

// Passo com estimativa de erro (dobrar o passo)
void rk4_passo_com_erro(double t, PenduloEstado *estado, double dt, PenduloParametros *params, double *erro);

// Resolve o sistema usando RK4 com passo constante
void rk4_resolver(PenduloEstado *estado_inicial, double t0, double tf, int n_passos, 
                  PenduloParametros *params, PenduloEstado *solucao, double *tempo);

// Resolve o sistema usando RK4 com passo adaptativo
int rk4_adaptativo(PenduloEstado *estado_inicial, double t0, double tf, double epsilon,
                   PenduloParametros *params, PenduloEstado **solucao, double **tempo, int max_passos);

// Calcula o período usando detecção de mudança de sinal e interpolação linear
double calcular_periodo(PenduloEstado *solucao, double *tempo, int n_pontos, int n_inversoes);

// Solução analítica linearizada
double solucao_analitica(double t, double theta0, PenduloParametros *params);

#endif
