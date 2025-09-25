#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vetor.h"
#include "matriz.h"
#include "sistlinear.h"
#include "mmq.h"

void teste_solucao_1() {
    int m = 5, n = 3;
    double** A = mat_cria(m, n);
    double b[] = {10, 10, -5, 15, 0};
    double x[3];

    A[0][0] = 3; A[0][1] = -1; A[0][2] = 2;
    A[1][0] = 4; A[1][1] = 1;  A[1][2] = 0;
    A[2][0] = -3;A[2][1] = 2;  A[2][2] = 1;
    A[3][0] = 1; A[3][1] = 1;  A[3][2] = 5;
    A[4][0] = -2;A[4][1] = 0;  A[4][2] = 3;

    double erro = mmq(m, n, A, b, x);

    printf("solucao:\n");
    printf("x[0] = %g\n", x[0]);
    printf("x[1] = %g\n", x[1]);
    printf("x[2] = %g\n", x[2]);

    double* Ax = vet_cria(m);
    mat_multv(m, n, A, x, Ax);
    printf("Ax:\n");
    for(int i=0; i<m; ++i) printf("Ax[%d] = %g\n", i, Ax[i]);

    printf("Erro: %g\n", erro);
    printf("-------------------------\n");

    vet_libera(Ax);
    mat_libera(m, A);
}

void teste_solucao_2() {
    int m = 5, n = 4;
    double** A = mat_cria(m, n);
    double b[] = {10, 0, 2, 0, 5};
    double x[4];

    A[0][0] = 4; A[0][1] = 2; A[0][2] = 3; A[0][3] = 0;
    A[1][0] = -2;A[1][1] = 3; A[1][2] = -1;A[1][3] = 1;
    A[2][0] = 1; A[2][1] = 3; A[2][2] = -4;A[2][3] = 2;
    A[3][0] = 1; A[3][1] = 0; A[3][2] = 1; A[3][3] = -1;
    A[4][0] = 3; A[4][1] = 1; A[4][2] = 3; A[4][3] = -2;

    double erro = mmq(m, n, A, b, x);

    printf("solucao:\n");
    printf("x[0] = %g\n", x[0]);
    printf("x[1] = %g\n", x[1]);
    printf("x[2] = %g\n", x[2]);
    printf("x[3] = %g\n", x[3]);

    double* Ax = vet_cria(m);
    mat_multv(m, n, A, x, Ax);
    printf("Ax:\n");
    for(int i=0; i<m; ++i) printf("Ax[%d] = %g\n", i, Ax[i]);

    printf("Erro: %g\n", erro);
    printf("-------------------------\n");

    vet_libera(Ax);
    mat_libera(m, A);
}

void teste_ajuste_curva_1() {
    int n = 4;
    double px[] = {-1.0, 0.0, 1.0, 2.0};
    double py[] = {1.0, 0.0, 0.0, -2.0};
    double a, b, c, d, erro;

    printf("parabola:\n");
    erro = ajuste_parabola(n, px, py, &a, &b, &c);
    printf("Erro: %g\n", erro);
    printf("a = %g  b = %g  c = %g\n", c, b, a); // Imprime c,b,a para bater com a saida

    printf("cubica:\n");
    erro = ajuste_cubica(n, px, py, &a, &b, &c, &d);
    printf("Erro: %g\n", erro);
    printf("a = %g  b = %g  c = %g  d = %g\n", d, c, b, a); // Imprime d,c,b,a para bater com a saida
    printf("-------------------------\n");
}

void teste_ajuste_curva_2() {
    int n = 4;
    double px[] = {0.0, 1.0, 2.0, 5.0};
    double py[] = {0.0, 3.0, 3.0, 6.0};
    double a, b, c, d, erro;

    printf("parabola:\n");
    erro = ajuste_parabola(n, px, py, &a, &b, &c);
    printf("Erro: %g\n", erro);
    printf("a = %g  b = %g  c = %g\n", c, b, a);

    printf("cubica:\n");
    erro = ajuste_cubica(n, px, py, &a, &b, &c, &d);
    printf("Erro: %g\n", erro);
    printf("a = %g  b = %g  c = %g  d = %g\n", d, c, b, a);
    printf("-------------------------\n");
}

void teste_ajuste_curva_3() {
    int n = 4;
    double px[] = {1.0, 3.0, 4.0, 6.0};
    double py[] = {2.0, 2.0, 1.0, 3.0};
    double a, b, c, d, erro;

    printf("parabola:\n");
    erro = ajuste_parabola(n, px, py, &a, &b, &c);
    printf("Erro: %g\n", erro);
    printf("a = %g  b = %g  c = %g\n", c, b, a);

    printf("cubica:\n");
    erro = ajuste_cubica(n, px, py, &a, &b, &c, &d);
    printf("Erro: %g\n", erro);
    printf("a = %g  b = %g  c = %g  d = %g\n", d, c, b, a);
    printf("-------------------------\n");
}

void teste_exponencial_1() {
    int n = 7;
    double px[] = {1950, 1955, 1960, 1965, 1970, 1975, 1980};
    double py[] = {53.05, 73.04, 98.31, 139.78, 193.48, 260.20, 320.39};
    double a, b, erro;

    printf("exponencial:\n");
    erro = ajuste_exponencial_exp(n, px, py, &a, &b);
    printf("Erroln: %g\n", erro);
    printf("a = %g  b = %g\n", a, b);
    printf("-------------------------\n");
}

void teste_exponencial_2() {
    int n = 7;
    double px[] = {0, 5, 10, 15, 20, 25, 30};
    double py[] = {53.05, 73.04, 98.31, 139.78, 193.48, 260.20, 320.39};
    double a, b, erro;

    printf("exponencial:\n");
    erro = ajuste_exponencial_exp(n, px, py, &a, &b);
    printf("Erroln: %g\n", erro);
    printf("a = %g  b = %g\n", a, b);
    printf("-------------------------\n");
}

int main() {
    teste_solucao_1();
    teste_solucao_2();
    teste_ajuste_curva_1();
    teste_ajuste_curva_2();
    teste_ajuste_curva_3();
    teste_exponencial_1();
    teste_exponencial_2();

    return 0;
}
