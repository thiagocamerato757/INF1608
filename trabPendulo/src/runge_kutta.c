#include "runge_kutta.h"
#include <math.h>
#include <stdlib.h>

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

// Resolve o sistema para múltiplos passos de tempo
void rk4_resolver(PenduloEstado *estado_inicial, double t0, double tf, int n_passos, 
                  PenduloParametros *params, PenduloEstado *solucao, double *tempo) {
    double dt = (tf - t0) / n_passos;
    double t = t0;
    
    // Copia o estado inicial
    solucao[0] = *estado_inicial;
    tempo[0] = t0;
    
    // Itera sobre todos os passos de tempo
    for (int i = 0; i < n_passos; i++) {
        rk4_passo(t, &solucao[i], dt, params);
        t += dt;
        
        // Salva o próximo estado
        if (i < n_passos - 1) {
            solucao[i+1] = solucao[i];
            tempo[i+1] = t;
        }
    }
    
    // Salva o estado final
    solucao[n_passos] = solucao[n_passos-1];
    tempo[n_passos] = tf;
}
