#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "runge_kutta.h"

#define PI 3.14159265358979323846
#define MAX_PASSOS 10000000

void executar_experimento(double theta0_graus, PenduloParametros *params) {
    printf("\n");
    printf("========================================\n");
    printf("Experimento: θ₀ = %.1f graus (%.4f rad)\n", theta0_graus, theta0_graus * PI / 180.0);
    printf("========================================\n");
    
    double theta0 = theta0_graus * PI / 180.0;
    
    // Período teórico da solução linearizada
    double T_teorico = 2.0 * PI * sqrt(params->L / params->g);
    printf("\nPeríodo teórico (linearizado): %.6f s\n", T_teorico);
    
    // Simular tempo suficiente para 10 períodos
    double tf = 10.0 * T_teorico * 1.5; // Margem de segurança
    
    printf("\n%-20s %-15s %-15s %-15s\n", "Método", "Período (s)", "Passos", "Tempo CPU (ms)");
    printf("--------------------------------------------------------------------------------\n");
    
    // 1. Solução analítica
    printf("%-20s %-15.6f %-15s %-15s\n", "Analítico", T_teorico, "N/A", "N/A");
    
    // 2. Passo constante h = 0.01
    {
        PenduloEstado estado_inicial = {theta0, 0.0};
        double h = 0.01;
        int n_passos = (int)(tf / h);
        
        PenduloEstado *solucao = malloc((n_passos + 1) * sizeof(PenduloEstado));
        double *tempo = malloc((n_passos + 1) * sizeof(double));
        
        clock_t inicio = clock();
        rk4_resolver(&estado_inicial, 0.0, tf, n_passos, params, solucao, tempo);
        double periodo = calcular_periodo(solucao, tempo, n_passos + 1, 11);
        clock_t fim = clock();
        
        double tempo_cpu = 1000.0 * (fim - inicio) / CLOCKS_PER_SEC;
        printf("%-20s %-15.6f %-15d %-15.2f\n", "h = 0.01", periodo, n_passos, tempo_cpu);
        
        free(solucao);
        free(tempo);
    }
    
    // 3. Passo constante h = 0.001
    {
        PenduloEstado estado_inicial = {theta0, 0.0};
        double h = 0.001;
        int n_passos = (int)(tf / h);
        
        PenduloEstado *solucao = malloc((n_passos + 1) * sizeof(PenduloEstado));
        double *tempo = malloc((n_passos + 1) * sizeof(double));
        
        clock_t inicio = clock();
        rk4_resolver(&estado_inicial, 0.0, tf, n_passos, params, solucao, tempo);
        double periodo = calcular_periodo(solucao, tempo, n_passos + 1, 11);
        clock_t fim = clock();
        
        double tempo_cpu = 1000.0 * (fim - inicio) / CLOCKS_PER_SEC;
        printf("%-20s %-15.6f %-15d %-15.2f\n", "h = 0.001", periodo, n_passos, tempo_cpu);
        
        free(solucao);
        free(tempo);
    }
    
    // 4. Passo constante h = 0.0001
    {
        PenduloEstado estado_inicial = {theta0, 0.0};
        double h = 0.0001;
        int n_passos = (int)(tf / h);
        
        PenduloEstado *solucao = malloc((n_passos + 1) * sizeof(PenduloEstado));
        double *tempo = malloc((n_passos + 1) * sizeof(double));
        
        clock_t inicio = clock();
        rk4_resolver(&estado_inicial, 0.0, tf, n_passos, params, solucao, tempo);
        double periodo = calcular_periodo(solucao, tempo, n_passos + 1, 11);
        clock_t fim = clock();
        
        double tempo_cpu = 1000.0 * (fim - inicio) / CLOCKS_PER_SEC;
        printf("%-20s %-15.6f %-15d %-15.2f\n", "h = 0.0001", periodo, n_passos, tempo_cpu);
        
        free(solucao);
        free(tempo);
    }
    
    // 5. Passo adaptativo
    {
        PenduloEstado estado_inicial = {theta0, 0.0};
        PenduloEstado *solucao;
        double *tempo;
        
        clock_t inicio = clock();
        int n_passos = rk4_adaptativo(&estado_inicial, 0.0, tf, 1e-5, params, &solucao, &tempo, MAX_PASSOS);
        double periodo = calcular_periodo(solucao, tempo, n_passos, 11);
        clock_t fim = clock();
        
        double tempo_cpu = 1000.0 * (fim - inicio) / CLOCKS_PER_SEC;
        printf("%-20s %-15.6f %-15d %-15.2f\n", "Adaptativo (ε=1e-5)", periodo, n_passos, tempo_cpu);
        
        free(solucao);
        free(tempo);
    }
    
    // Calcular erro da aproximação linearizada
    PenduloEstado estado_inicial = {theta0, 0.0};
    double h = 0.0001;
    int n_passos = (int)(tf / h);
    
    PenduloEstado *solucao = malloc((n_passos + 1) * sizeof(PenduloEstado));
    double *tempo = malloc((n_passos + 1) * sizeof(double));
    rk4_resolver(&estado_inicial, 0.0, tf, n_passos, params, solucao, tempo);
    double T_numerico = calcular_periodo(solucao, tempo, n_passos + 1, 11);
    double erro_relativo = fabs(T_numerico - T_teorico) / T_numerico;
    
    printf("\nErro da aproximação linearizada: %.6f (%.4f%%)\n", 
           fabs(T_numerico - T_teorico), erro_relativo * 100.0);
    
    free(solucao);
    free(tempo);
}

void gerar_graficos_comparacao(double theta0_graus, PenduloParametros *params) {
    printf("\nGerando dados para gráficos (θ₀ = %.1f°)...\n", theta0_graus);
    
    double theta0 = theta0_graus * PI / 180.0;
    double T_teorico = 2.0 * PI * sqrt(params->L / params->g);
    double tf = T_teorico * 1.2; // Um ciclo completo
    
    // Passo fino para boa resolução
    double h = 0.0001;
    int n_passos = (int)(tf / h);
    
    PenduloEstado estado_inicial = {theta0, 0.0};
    PenduloEstado *solucao = malloc((n_passos + 1) * sizeof(PenduloEstado));
    double *tempo = malloc((n_passos + 1) * sizeof(double));
    
    rk4_resolver(&estado_inicial, 0.0, tf, n_passos, params, solucao, tempo);
    
    // Salvar dados
    char filename[256];
    snprintf(filename, sizeof(filename), "data/comparacao_theta%.0f.txt", theta0_graus);
    
    FILE *fp = fopen(filename, "w");
    if (fp) {
        fprintf(fp, "# Comparação: Solução Numérica vs Solução Analítica\n");
        fprintf(fp, "# θ₀ = %.4f rad (%.1f graus)\n", theta0, theta0_graus);
        fprintf(fp, "# t(s)\ttheta_num(rad)\ttheta_anal(rad)\tdiferenca(rad)\n");
        
        for (int i = 0; i <= n_passos; i++) {
            double theta_anal = solucao_analitica(tempo[i], theta0, params);
            double diferenca = fabs(solucao[i].theta - theta_anal);
            
            // Se a diferença for muito pequena (< 1e-10), considerar como zero
            if (diferenca < 1e-10) {
                diferenca = 0.0;
            }
            
            fprintf(fp, "%.6f\t%.6f\t%.6f\t%.6e\n", 
                    tempo[i], 
                    solucao[i].theta, 
                    theta_anal,
                    diferenca);
        }
        fclose(fp);
        printf("✓ Dados salvos em: %s\n", filename);
    }
    
    free(solucao);
    free(tempo);
}

int main(int argc, char *argv[]) {
    printf("========================================\n");
    printf("  Simulação de Pêndulo - Projeto INF1608\n");
    printf("  Método: Runge-Kutta 4ª Ordem\n");
    printf("========================================\n");
    
    // Parâmetros do pêndulo
    PenduloParametros params;
    params.g = 9.81;  // m/s²
    params.L = 1.0;   // m
    
    printf("\nParâmetros físicos:\n");
    printf("  g = %.2f m/s²\n", params.g);
    printf("  L = %.2f m\n", params.L);
    
    if (argc > 1 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        printf("\nUso: %s [opção]\n", argv[0]);
        printf("\nOpções:\n");
        printf("  (nenhuma)   Executa experimentos completos\n");
        printf("  --help, -h  Mostra esta ajuda\n");
        return 0;
    }
    
    // Criar diretórios necessários
    int ret = system("mkdir -p data");
    (void)ret;
    
    // Experimentos com diferentes ângulos iniciais
    double angulos[] = {5.0, 10.0, 30.0, 45.0, 60.0, 90.0, 120.0, 150.0};
    int n_angulos = sizeof(angulos) / sizeof(angulos[0]);
    
    for (int i = 0; i < n_angulos; i++) {
        executar_experimento(angulos[i], &params);
    }
    
    // Gerar dados para gráficos de alguns casos
    printf("\n========================================\n");
    printf("Gerando dados para gráficos\n");
    printf("========================================\n");
    gerar_graficos_comparacao(10.0, &params);
    gerar_graficos_comparacao(45.0, &params);
    gerar_graficos_comparacao(90.0, &params);
    
    // Encontrar ângulo máximo para erro < 0.001
    printf("\n========================================\n");
    printf("Análise: Ângulo máximo para erro < 0.001\n");
    printf("========================================\n");
    
    double T_teorico = 2.0 * PI * sqrt(params.L / params.g);
    
    for (double theta_deg = 1.0; theta_deg <= 180.0; theta_deg += 1.0) {
        double theta0 = theta_deg * PI / 180.0;
        PenduloEstado estado_inicial = {theta0, 0.0};
        
        double tf = 10.0 * T_teorico;
        double h = 0.0001;
        int n_passos = (int)(tf / h);
        
        PenduloEstado *solucao = malloc((n_passos + 1) * sizeof(PenduloEstado));
        double *tempo = malloc((n_passos + 1) * sizeof(double));
        
        rk4_resolver(&estado_inicial, 0.0, tf, n_passos, &params, solucao, tempo);
        double T_numerico = calcular_periodo(solucao, tempo, n_passos + 1, 11);
        
        double erro = fabs(T_numerico - T_teorico);
        
        if (erro >= 0.001) {
            printf("Ângulo máximo: %.1f graus\n", theta_deg - 1.0);
            printf("(Para θ₀ = %.1f°, erro = %.6f)\n", theta_deg, erro);
            free(solucao);
            free(tempo);
            break;
        }
        
        free(solucao);
        free(tempo);
    }
    
    printf("\n✓ Experimentos concluídos!\n");
    printf("✓ Dados salvos em data/\n");
    
    return 0;
}
