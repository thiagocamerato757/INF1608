#include "gradconj.h"
#include "vetor.h"
#include "matriz.h"
#include <stdlib.h>
#include <math.h>

int gradconj(int n, double** A, double* b, double* x, double tol) {
    double* r = vet_cria(n);
    double* d = vet_cria(n);
    double* Ad = vet_cria(n);
    double* temp = vet_cria(n);
    
    // x0 = estimativa inicial (já fornecida)
    // r0 = b - Ax0
    mat_multv(n, n, A, x, temp);
    for (int i = 0; i < n; i++) {
        r[i] = b[i] - temp[i];
    }
    
    // d0 = r0
    for (int i = 0; i < n; i++) {
        d[i] = r[i];
    }
    
    int k;
    for (k = 0; k < n; k++) {
        double norm_r = vet_norma2(n, r);
        if (norm_r < tol) {
            break;
        }
        
        // alpha_k = (r_k^T * r_k) / (d_k^T * A * d_k)
        mat_multv(n, n, A, d, Ad);
        double rTr = vet_escalar(n, r, r);
        double dTAd = vet_escalar(n, d, Ad);
        double alpha = rTr / dTAd;
        
        // x_{k+1} = x_k + alpha_k * d_k
        for (int i = 0; i < n; i++) {
            x[i] = x[i] + alpha * d[i];
        }
        
        // r_{k+1} = r_k - alpha_k * A * d_k
        for (int i = 0; i < n; i++) {
            r[i] = r[i] - alpha * Ad[i];
        }
        
        // beta_k = (r_{k+1}^T * r_{k+1}) / (r_k^T * r_k)
        double rTr_new = vet_escalar(n, r, r);
        double beta = rTr_new / rTr;
        
        // d_{k+1} = r_{k+1} + beta_k * d_k
        for (int i = 0; i < n; i++) {
            d[i] = r[i] + beta * d[i];
        }
    }
    
    vet_libera(r);
    vet_libera(d);
    vet_libera(Ad);
    vet_libera(temp);
    
    return k;
}

int gradconj_jacobi(int n, double** A, double* b, double* x, double tol) {
    double* r = vet_cria(n);
    double* d = vet_cria(n);
    double* z = vet_cria(n);
    double* Ad = vet_cria(n);
    double* temp = vet_cria(n);
    double* M_inv = vet_cria(n);
    
    // M^-1 = diagonal inversa de A (pré-condicionador de Jacobi)
    for (int i = 0; i < n; i++) {
        M_inv[i] = 1.0 / A[i][i];
    }
    
    // x0 = estimativa inicial (já fornecida)
    // r0 = b - Ax0
    mat_multv(n, n, A, x, temp);
    for (int i = 0; i < n; i++) {
        r[i] = b[i] - temp[i];
    }
    
    // z0 = M^-1 * r0
    for (int i = 0; i < n; i++) {
        z[i] = M_inv[i] * r[i];
    }
    
    // d0 = z0
    for (int i = 0; i < n; i++) {
        d[i] = z[i];
    }
    
    int k;
    for (k = 0; k < n; k++) {
        double norm_r = vet_norma2(n, r);
        if (norm_r < tol) {
            break;
        }
        
        // alpha_k = (r_k^T * z_k) / (d_k^T * A * d_k)
        mat_multv(n, n, A, d, Ad);
        double rTz = vet_escalar(n, r, z);
        double dTAd = vet_escalar(n, d, Ad);
        double alpha = rTz / dTAd;
        
        // x_{k+1} = x_k + alpha_k * d_k
        for (int i = 0; i < n; i++) {
            x[i] = x[i] + alpha * d[i];
        }
        
        // r_{k+1} = r_k - alpha_k * A * d_k
        for (int i = 0; i < n; i++) {
            r[i] = r[i] - alpha * Ad[i];
        }
        
        // z_{k+1} = M^-1 * r_{k+1}
        for (int i = 0; i < n; i++) {
            z[i] = M_inv[i] * r[i];
        }
        
        // beta_k = (r_{k+1}^T * z_{k+1}) / (r_k^T * z_k)
        double rTz_new = vet_escalar(n, r, z);
        double beta = rTz_new / rTz;
        
        // d_{k+1} = z_{k+1} + beta_k * d_k
        for (int i = 0; i < n; i++) {
            d[i] = z[i] + beta * d[i];
        }
    }
    
    vet_libera(r);
    vet_libera(d);
    vet_libera(z);
    vet_libera(Ad);
    vet_libera(temp);
    vet_libera(M_inv);
    
    return k;
}