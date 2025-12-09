#include "runge_kutta.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

// Calcula as derivadas do sistema de EDOs do pêndulo
// Sistema: dθ/dt = ω, dω/dt = -(g/L)sin(θ)
void pendulo_derivada(double t __attribute__((unused)), PenduloEstado *estado, PenduloEstado *derivada, PenduloParametros *params) {
    derivada->theta = estado->omega;
    derivada->omega = -(params->g / params->L) * sin(estado->theta);
}

// Executa um passo do método de Runge-Kutta de 4ª ordem
void rk4_passo(double t, PenduloEstado *estado, double dt, PenduloParametros *params) {
    PenduloEstado k1, k2, k3, k4;
    PenduloEstado temp;
    
    // k1 = f(t, y)
    pendulo_derivada(t, estado, &k1, params);
    
    // k2 = f(t + dt/2, y + k1*dt/2)
    temp.theta = estado->theta + k1.theta * dt / 2.0;
    temp.omega = estado->omega + k1.omega * dt / 2.0;
    pendulo_derivada(t + dt/2.0, &temp, &k2, params);
    
    // k3 = f(t + dt/2, y + k2*dt/2)
    temp.theta = estado->theta + k2.theta * dt / 2.0;
    temp.omega = estado->omega + k2.omega * dt / 2.0;
    pendulo_derivada(t + dt/2.0, &temp, &k3, params);
    
    // k4 = f(t + dt, y + k3*dt)
    temp.theta = estado->theta + k3.theta * dt;
    temp.omega = estado->omega + k3.omega * dt;
    pendulo_derivada(t + dt, &temp, &k4, params);
    
    // y_new = y + (dt/6) * (k1 + 2*k2 + 2*k3 + k4)
    estado->theta += (dt / 6.0) * (k1.theta + 2.0*k2.theta + 2.0*k3.theta + k4.theta);
    estado->omega += (dt / 6.0) * (k1.omega + 2.0*k2.omega + 2.0*k3.omega + k4.omega);
}

// Passo com estimativa de erro (estratégia de dobrar o passo)
void rk4_passo_com_erro(double t, PenduloEstado *estado, double dt, PenduloParametros *params, double *erro) {
    PenduloEstado estado1 = *estado;
    PenduloEstado estado2 = *estado;
    
    // Um passo com h
    rk4_passo(t, &estado1, dt, params);
    
    // Dois passos com h/2
    rk4_passo(t, &estado2, dt/2.0, params);
    rk4_passo(t + dt/2.0, &estado2, dt/2.0, params);
    
    // Erro estimado (norma do vetor de diferença)
    double erro_theta = fabs(estado2.theta - estado1.theta);
    double erro_omega = fabs(estado2.omega - estado1.omega);
    *erro = fmax(erro_theta, erro_omega);
    
    // Usar a solução de dois passos (mais precisa)
    *estado = estado2;
}

// Resolve o sistema para múltiplos passos de tempo com passo constante
void rk4_resolver(PenduloEstado *estado_inicial, double t0, double tf, int n_passos, 
                  PenduloParametros *params, PenduloEstado *solucao, double *tempo) {
    double dt = (tf - t0) / n_passos;
    double t = t0;
    
    // Copia o estado inicial
    solucao[0] = *estado_inicial;
    tempo[0] = t0;
    
    // Itera sobre todos os passos de tempo
    for (int i = 0; i < n_passos; i++) {
        solucao[i+1] = solucao[i];
        rk4_passo(t, &solucao[i+1], dt, params);
        t += dt;
        tempo[i+1] = t;
    }
}

// Resolve o sistema usando RK4 com passo adaptativo
int rk4_adaptativo(PenduloEstado *estado_inicial, double t0, double tf, double epsilon,
                   PenduloParametros *params, PenduloEstado **solucao, double **tempo, int max_passos) {
    // Aloca arrays iniciais
    *solucao = malloc(max_passos * sizeof(PenduloEstado));
    *tempo = malloc(max_passos * sizeof(double));
    
    if (!(*solucao) || !(*tempo)) {
        return -1;
    }
    
    (*solucao)[0] = *estado_inicial;
    (*tempo)[0] = t0;
    
    double t = t0;
    double dt = 0.01; // Passo inicial
    int n = 0;
    
    while (t < tf && n < max_passos - 1) {
        PenduloEstado estado_teste = (*solucao)[n];
        double erro;
        
        // Ajusta passo para não ultrapassar tf
        if (t + dt > tf) {
            dt = tf - t;
        }
        
        // Tenta um passo e calcula o erro
        rk4_passo_com_erro(t, &estado_teste, dt, params, &erro);
        
        // Se o erro é aceitável, aceita o passo
        if (erro < epsilon || dt < 1e-10) {
            n++;
            (*solucao)[n] = estado_teste;
            t += dt;
            (*tempo)[n] = t;
            
            // Aumenta o passo se o erro é muito pequeno
            if (erro < epsilon / 10.0 && dt < 0.1) {
                dt *= 1.5;
            }
        } else {
            // Reduz o passo se o erro é muito grande
            dt *= 0.5;
        }
    }
    
    return n + 1;
}

// Calcula o período usando detecção de mudança de sinal e interpolação linear
double calcular_periodo(PenduloEstado *solucao, double *tempo, int n_pontos, int n_inversoes) {
    int inversoes_encontradas = 0;
    double t_primeira = -1.0;
    double t_ultima = -1.0;
    
    for (int i = 1; i < n_pontos; i++) {
        double v1 = solucao[i-1].omega;
        double v2 = solucao[i].omega;
        
        // Detecta mudança de sinal
        if (v1 * v2 <= 0.0) {
            // Interpolação linear
            double t_inversao = tempo[i-1] + fabs(v1) / (fabs(v1) + fabs(v2)) * (tempo[i] - tempo[i-1]);
            
            if (t_primeira < 0.0) {
                t_primeira = t_inversao;
            }
            t_ultima = t_inversao;
            
            inversoes_encontradas++;
            if (inversoes_encontradas >= n_inversoes) {
                break;
            }
        }
    }
    
    if (inversoes_encontradas < 2) {
        return -1.0; // Não encontrou inversões suficientes
    }
    
    // T = 2 * (tempo entre inversões) / (n_inversoes - 1)
    // Cada meio-período é uma inversão
    return 2.0 * (t_ultima - t_primeira) / (inversoes_encontradas - 1);
}

// Solução analítica linearizada: θ(t) = θ₀ cos(√(g/L) t)
double solucao_analitica(double t, double theta0, PenduloParametros *params) {
    double omega = sqrt(params->g / params->L);
    return theta0 * cos(omega * t);
}
