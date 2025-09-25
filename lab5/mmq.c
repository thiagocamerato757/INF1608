#include "mmq.h"
#include "matriz.h"
#include "sistlinear.h"
#include "vetor.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

double mmq (int m, int n, double** A, double* b, double* x) {
    double** AT = mat_cria(n, m);
    mat_transposta(m, n, A, AT);
    
    double** ATA = mat_cria(n, n);
    mat_multm(n, m, n, AT, A, ATA);
    
    double* ATb = vet_cria(n);
    mat_multv(n, m, AT, b, ATb);
    
    double** ATA_clone = mat_cria(n, n);
    for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) ATA_clone[i][j] = ATA[i][j];

    double* ATb_clone = vet_cria(n);
    for(int i=0; i<n; ++i) ATb_clone[i] = ATb[i];

    gauss(n, ATA_clone, ATb_clone, x);
    
    double* Ax = vet_cria(m);
    mat_multv(m, n, A, x, Ax);
    
    double* res = vet_cria(m);
    for (int i = 0; i < m; i++) {
        res[i] = b[i] - Ax[i];
    }
    
    double erro = vet_norma2(m, res);
    
    mat_libera(n, AT);
    mat_libera(n, ATA);
    mat_libera(n, ATA_clone);
    vet_libera(ATb);
    vet_libera(ATb_clone);
    vet_libera(Ax);
    vet_libera(res);
    
    return erro;
}

double ajuste_parabola (int n, double* px, double* py, double* a, double* b, double* c) {
    double** A = mat_cria(n, 3);
    for (int i = 0; i < n; i++) {
        A[i][0] = 1.0;
        A[i][1] = px[i];
        A[i][2] = px[i] * px[i];
    }
    
    double x[3];
    double erro = mmq(n, 3, A, py, x);
    
    *a = x[0];
    *b = x[1];
    *c = x[2];
    
    mat_libera(n, A);
    
    return erro;
}

double ajuste_cubica (int n, double* px, double* py, double* a, double* b, double* c, double* d) {
    double** A = mat_cria(n, 4);
    for (int i = 0; i < n; i++) {
        A[i][0] = 1.0;
        A[i][1] = px[i];
        A[i][2] = px[i] * px[i];
        A[i][3] = px[i] * px[i] * px[i];
    }
    
    double x[4];
    double erro = mmq(n, 4, A, py, x);
    
    *a = x[0];
    *b = x[1];
    *c = x[2];
    *d = x[3];
    
    mat_libera(n, A);
    
    return erro;
}

double ajuste_exponencial_exp (int n, double* px, double* py, double* a, double* b) {
    double* lny = vet_cria(n);
    for (int i = 0; i < n; i++) {
        lny[i] = log(py[i]);
    }
    
    double** A = mat_cria(n, 2);
    for (int i = 0; i < n; i++) {
        A[i][0] = 1.0;
        A[i][1] = px[i];
    }
    
    double x[2];
    double erro = mmq(n, 2, A, lny, x);
    
    *a = exp(x[0]);
    *b = x[1];
    
    vet_libera(lny);
    mat_libera(n, A);
    
    return erro;
}
