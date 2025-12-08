#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "runge_kutta.h"

#define PI 3.14159265358979323846

void mostrar_uso(const char *programa) {
    printf("Uso: %s [theta_graus] [omega] [tempo_final] [n_passos]\n", programa);
    printf("\n");
    printf("Parâmetros:\n");
    printf("  theta_graus  - Ângulo inicial em graus (padrão: 45.0)\n");
    printf("  omega        - Velocidade angular inicial em rad/s (padrão: 0.0)\n");
    printf("  tempo_final  - Tempo final de simulação em segundos (padrão: 10.0)\n");
    printf("  n_passos     - Número de passos de integração (padrão: 1000)\n");
    printf("\n");
    printf("Exemplos:\n");
    printf("  %s                    # Usa valores padrão\n", programa);
    printf("  %s 30 0 10 1000       # θ=30°, ω=0, t=10s, 1000 passos\n", programa);
    printf("  %s 90 2.0 15 2000     # θ=90°, ω=2.0 rad/s, t=15s, 2000 passos\n", programa);
    printf("\n");
}

int main(int argc, char *argv[]) {
    printf("========================================\n");
    printf("  Simulação de Pêndulo - Método RK4   \n");
    printf("========================================\n\n");
    
    // Valores padrão
    double theta_graus = 45.0;
    double omega_inicial = 0.0;
    double tf = 10.0;
    int n_passos = 1000;
    
    // Processar argumentos de linha de comando
    if (argc > 1) {
        if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
            mostrar_uso(argv[0]);
            return 0;
        }
        
        if (argc != 5) {
            fprintf(stderr, "Erro: Número incorreto de argumentos.\n\n");
            mostrar_uso(argv[0]);
            return 1;
        }
        
        theta_graus = atof(argv[1]);
        omega_inicial = atof(argv[2]);
        tf = atof(argv[3]);
        n_passos = atoi(argv[4]);
        
        // Validação básica
        if (n_passos <= 0) {
            fprintf(stderr, "Erro: Número de passos deve ser positivo.\n");
            return 1;
        }
        if (tf <= 0) {
            fprintf(stderr, "Erro: Tempo final deve ser positivo.\n");
            return 1;
        }
    }
    
    // Parâmetros do pêndulo
    PenduloParametros params;
    params.g = 9.81;  // m/s²
    params.L = 1.0;   // m
    
    // Condições iniciais
    PenduloEstado estado_inicial;
    estado_inicial.theta = theta_graus * PI / 180.0;  // Converter para radianos
    estado_inicial.omega = omega_inicial;  // rad/s
    
    // Parâmetros de simulação
    double t0 = 0.0;
    
    printf("Parâmetros da simulação:\n");
    printf("  g = %.2f m/s²\n", params.g);
    printf("  L = %.2f m\n", params.L);
    printf("  θ₀ = %.4f rad (%.2f°)\n", estado_inicial.theta, theta_graus);
    printf("  ω₀ = %.4f rad/s\n", omega_inicial);
    printf("  Tempo: %.2f s\n", tf);
    printf("  Passos: %d\n", n_passos);
    printf("  dt = %.6f s\n", (tf - t0) / n_passos);
    printf("\n");
    
    // Alocar memória para a solução
    PenduloEstado *solucao = malloc((n_passos + 1) * sizeof(PenduloEstado));
    double *tempo = malloc((n_passos + 1) * sizeof(double));
    
    if (!solucao || !tempo) {
        fprintf(stderr, "Erro ao alocar memória!\n");
        return 1;
    }
    
    // Resolver o sistema
    printf("Resolvendo... ");
    fflush(stdout);
    rk4_resolver(&estado_inicial, t0, tf, n_passos, &params, solucao, tempo);
    printf("OK\n\n");
    
    // Salvar resultados em arquivo
    FILE *fp = fopen("data/pendulo_data.txt", "w");
    if (!fp) {
        fprintf(stderr, "Erro ao criar arquivo de dados!\n");
        free(solucao);
        free(tempo);
        return 1;
    }
    
    fprintf(fp, "# t (s)\ttheta (rad)\tomega (rad/s)\ttheta (graus)\n");
    for (int i = 0; i <= n_passos; i++) {
        fprintf(fp, "%.6f\t%.6f\t%.6f\t%.6f\n", 
                tempo[i], 
                solucao[i].theta, 
                solucao[i].omega,
                solucao[i].theta * 180.0 / PI);
    }
    fclose(fp);
    printf("✓ Dados salvos em: data/pendulo_data.txt\n");
    
    // Calcular e salvar energia
    fp = fopen("data/energia.txt", "w");
    if (fp) {
        fprintf(fp, "# t (s)\tEnergia (normalizada)\n");
        for (int i = 0; i <= n_passos; i++) {
            double E = 0.5 * params.L * solucao[i].omega * solucao[i].omega + 
                       params.g * (1.0 - cos(solucao[i].theta));
            fprintf(fp, "%.6f\t%.8f\n", tempo[i], E);
        }
        fclose(fp);
        printf("✓ Dados de energia salvos em: data/energia.txt\n");
    }
    
    // Estatísticas finais
    printf("\nResultados finais:\n");
    printf("  θ(tf) = %.6f rad (%.2f°)\n", 
           solucao[n_passos].theta, 
           solucao[n_passos].theta * 180.0 / PI);
    printf("  ω(tf) = %.6f rad/s\n", solucao[n_passos].omega);
    
    // Calcular conservação de energia
    double E_inicial = 0.5 * params.L * solucao[0].omega * solucao[0].omega + 
                       params.g * (1.0 - cos(solucao[0].theta));
    double E_final = 0.5 * params.L * solucao[n_passos].omega * solucao[n_passos].omega + 
                     params.g * (1.0 - cos(solucao[n_passos].theta));
    printf("\nConservação de energia:\n");
    printf("  E_inicial = %.8f\n", E_inicial);
    printf("  E_final   = %.8f\n", E_final);
    printf("  ΔE/E      = %.6e\n", fabs(E_final - E_inicial) / E_inicial);
    
    // Liberar memória
    free(solucao);
    free(tempo);
    
    printf("\n✓ Simulação concluída com sucesso!\n");
    return 0;
}
