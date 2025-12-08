#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "../src/runge_kutta.h"

#define PI 3.14159265358979323846

// Teste básico do método RK4
void teste_pequeno_angulo() {
    printf("=== Teste 1: Pequenos ângulos (aproximação harmônica) ===\n");
    
    PenduloEstado estado;
    estado.theta = 0.1;  // ~5.7 graus
    estado.omega = 0.0;
    
    PenduloParametros params;
    params.g = 9.81;
    params.L = 1.0;
    
    // Período teórico: T = 2π√(L/g) ≈ 2.006 s
    double T_teorico = 2.0 * PI * sqrt(params.L / params.g);
    printf("Período teórico (pequenos ângulos): %.4f s\n", T_teorico);
    
    // Simular um período
    int n_passos = 1000;
    PenduloEstado *solucao = malloc((n_passos + 1) * sizeof(PenduloEstado));
    double *tempo = malloc((n_passos + 1) * sizeof(double));
    
    rk4_resolver(&estado, 0.0, T_teorico, n_passos, &params, solucao, tempo);
    
    printf("Estado inicial: θ = %.6f rad, ω = %.6f rad/s\n", 
           solucao[0].theta, solucao[0].omega);
    printf("Estado final:   θ = %.6f rad, ω = %.6f rad/s\n", 
           solucao[n_passos].theta, solucao[n_passos].omega);
    printf("Diferença em θ: %.6f rad\n", fabs(solucao[n_passos].theta - solucao[0].theta));
    
    free(solucao);
    free(tempo);
    printf("\n");
}

// Teste de conservação de energia
void teste_conservacao_energia() {
    printf("=== Teste 2: Conservação de energia ===\n");
    
    PenduloEstado estado;
    estado.theta = PI / 4.0;  // 45 graus
    estado.omega = 0.0;
    
    PenduloParametros params;
    params.g = 9.81;
    params.L = 1.0;
    
    int n_passos = 1000;
    PenduloEstado *solucao = malloc((n_passos + 1) * sizeof(PenduloEstado));
    double *tempo = malloc((n_passos + 1) * sizeof(double));
    
    rk4_resolver(&estado, 0.0, 10.0, n_passos, &params, solucao, tempo);
    
    // Energia = (1/2)*m*L²*ω² + m*g*L*(1-cos(θ))
    // Normalizando por m*L:
    double E_inicial = 0.5 * params.L * solucao[0].omega * solucao[0].omega + 
                       params.g * (1.0 - cos(solucao[0].theta));
    double E_final = 0.5 * params.L * solucao[n_passos].omega * solucao[n_passos].omega + 
                     params.g * (1.0 - cos(solucao[n_passos].theta));
    
    printf("Energia inicial: %.8f\n", E_inicial);
    printf("Energia final:   %.8f\n", E_final);
    printf("Variação relativa: %.6e\n", fabs(E_final - E_inicial) / E_inicial);
    
    free(solucao);
    free(tempo);
    printf("\n");
}

// Teste com grande amplitude
void teste_grande_amplitude() {
    printf("=== Teste 3: Grande amplitude ===\n");
    
    PenduloEstado estado;
    estado.theta = 2.0;  // ~114 graus
    estado.omega = 0.0;
    
    PenduloParametros params;
    params.g = 9.81;
    params.L = 1.0;
    
    int n_passos = 2000;
    PenduloEstado *solucao = malloc((n_passos + 1) * sizeof(PenduloEstado));
    double *tempo = malloc((n_passos + 1) * sizeof(double));
    
    rk4_resolver(&estado, 0.0, 10.0, n_passos, &params, solucao, tempo);
    
    printf("Amplitude inicial: %.4f rad (%.1f graus)\n", 
           estado.theta, estado.theta * 180.0 / PI);
    printf("Simulação de %.1f segundos com %d passos\n", 10.0, n_passos);
    printf("Estado final: θ = %.6f rad, ω = %.6f rad/s\n", 
           solucao[n_passos].theta, solucao[n_passos].omega);
    
    free(solucao);
    free(tempo);
    printf("\n");
}

int main() {
    printf("===============================================\n");
    printf("  Testes do Método de Runge-Kutta 4ª Ordem   \n");
    printf("  Simulação de Pêndulo                        \n");
    printf("===============================================\n\n");
    
    teste_pequeno_angulo();
    teste_conservacao_energia();
    teste_grande_amplitude();
    
    printf("Testes concluídos!\n");
    return 0;
}
