#include "raiz.h"
#include <math.h>

int bissecao(double a, double b, double (*f)(double x), double* r) {
    // Verifica se há mudança de sinal no intervalo
    double fa = f(a);
    double fb = f(b);
    
    // Se não houver mudança de sinal, retorna -1
    if (fa * fb >= 0) {
        return -1;
    }
    
    // Inicializa variáveis
    int iterations = 0;
    double c, fc;
    double error = (b - a) / 2.0;
    const double max_error = 0.5e-8;  // Precisão de 8 dígitos
    const double tolerance = 1e-12;   // Tolerância para |f(c)| < 1e-12
    
    // Loop do método da bisseção
    while (error >= max_error) {
        iterations++;
        c = (a + b) / 2.0;
        fc = f(c);
        
        // Verifica se encontramos uma raiz exata ou se |f(c)| < tolerância
        if (fabs(fc) < tolerance) {
            *r = c;
            return iterations;
        }
        
        // Atualiza o intervalo com base na mudança de sinal
        if (fa * fc < 0) {
            // Raiz está em [a, c]
            b = c;
            fb = fc;
        } else {
            // Raiz está em [c, b]
            a = c;
            fa = fc;
        }
        
        // Atualiza o erro
        error = (b - a) / 2.0;
    }
    
    // Retorna o ponto médio do intervalo final como estimativa da raiz
    *r = (a + b) / 2.0;
    return iterations;
}