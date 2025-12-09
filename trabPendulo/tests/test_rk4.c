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
    
    // Simular 10 períodos
    double tf = 10.0 * T_teorico;
    int n_passos = 10000;
    PenduloEstado *solucao = malloc((n_passos + 1) * sizeof(PenduloEstado));
    double *tempo = malloc((n_passos + 1) * sizeof(double));
    
    rk4_resolver(&estado, 0.0, tf, n_passos, &params, solucao, tempo);
    
    // Calcular período numérico
    double T_numerico = calcular_periodo(solucao, tempo, n_passos + 1, 11);
    printf("Período numérico: %.6f s\n", T_numerico);
    printf("Erro relativo: %.6f%%\n", fabs(T_numerico - T_teorico) / T_teorico * 100.0);
    
    free(solucao);
    free(tempo);
    printf("\n");
}

// Teste de comparação com solução analítica
void teste_solucao_analitica() {
    printf("=== Teste 2: Comparação com solução analítica ===\n");
    
    PenduloEstado estado;
    estado.theta = 0.174533;  // 10 graus
    estado.omega = 0.0;
    
    PenduloParametros params;
    params.g = 9.81;
    params.L = 1.0;
    
    int n_passos = 1000;
    PenduloEstado *solucao = malloc((n_passos + 1) * sizeof(PenduloEstado));
    double *tempo = malloc((n_passos + 1) * sizeof(double));
    
    double tf = 2.0;
    rk4_resolver(&estado, 0.0, tf, n_passos, &params, solucao, tempo);
    
    // Comparar com solução analítica em alguns pontos
    double max_erro = 0.0;
    for (int i = 0; i <= n_passos; i++) {
        double theta_anal = solucao_analitica(tempo[i], estado.theta, &params);
        double erro = fabs(solucao[i].theta - theta_anal);
        if (erro > max_erro) max_erro = erro;
    }
    
    printf("Erro máximo vs solução analítica: %.6e rad\n", max_erro);
    printf("Erro máximo em graus: %.6f°\n", max_erro * 180.0 / PI);
    
    free(solucao);
    free(tempo);
    printf("\n");
}

// Teste com passo adaptativo
void teste_passo_adaptativo() {
    printf("=== Teste 3: Passo adaptativo ===\n");
    
    PenduloEstado estado;
    estado.theta = PI / 4.0;  // 45 graus
    estado.omega = 0.0;
    
    PenduloParametros params;
    params.g = 9.81;
    params.L = 1.0;
    
    PenduloEstado *solucao;
    double *tempo;
    
    double tf = 10.0;
    int n_passos = rk4_adaptativo(&estado, 0.0, tf, 1e-5, &params, &solucao, &tempo, 1000000);
    
    printf("Simulação de %.1f segundos\n", tf);
    printf("Número de passos adaptativos: %d\n", n_passos);
    printf("Passo médio: %.6f s\n", tf / n_passos);
    
    // Calcular período
    double T = calcular_periodo(solucao, tempo, n_passos, 11);
    printf("Período calculado: %.6f s\n", T);
    
    free(solucao);
    free(tempo);
    printf("\n");
}

// Teste de cálculo do período
void teste_calculo_periodo() {
    printf("=== Teste 4: Cálculo do período ===\n");
    
    double angulos[] = {10.0, 30.0, 60.0, 90.0};
    
    PenduloParametros params;
    params.g = 9.81;
    params.L = 1.0;
    
    double T_teorico = 2.0 * PI * sqrt(params.L / params.g);
    
    printf("Período teórico (linearizado): %.6f s\n\n", T_teorico);
    printf("Ângulo (°)  Período (s)  Erro (%%)\n");
    printf("----------------------------------------\n");
    
    for (size_t i = 0; i < sizeof(angulos)/sizeof(angulos[0]); i++) {
        double theta0 = angulos[i] * PI / 180.0;
        
        PenduloEstado estado;
        estado.theta = theta0;
        estado.omega = 0.0;
        
        double tf = 20.0;
        int n_passos = 20000;
        PenduloEstado *solucao = malloc((n_passos + 1) * sizeof(PenduloEstado));
        double *tempo = malloc((n_passos + 1) * sizeof(double));
        
        rk4_resolver(&estado, 0.0, tf, n_passos, &params, solucao, tempo);
        double T = calcular_periodo(solucao, tempo, n_passos + 1, 11);
        
        double erro = fabs(T - T_teorico) / T * 100.0;
        printf("%8.1f    %10.6f  %8.4f\n", angulos[i], T, erro);
        
        free(solucao);
        free(tempo);
    }
    
    printf("\n");
}

int main() {
    printf("===============================================\n");
    printf("  Testes do Método de Runge-Kutta 4ª Ordem   \n");
    printf("  Simulação de Pêndulo                        \n");
    printf("===============================================\n\n");
    
    teste_pequeno_angulo();
    teste_solucao_analitica();
    teste_passo_adaptativo();
    teste_calculo_periodo();
    
    printf("Testes concluídos!\n");
    return 0;
}
