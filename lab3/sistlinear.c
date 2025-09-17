#include "sistlinear.h"
#include "matriz.h"
#include "vetor.h"
#include <math.h>

void gauss(int n, double** A, double* b, double* x) {
    // Create a copy of the matrix and vector to avoid modifying the originals
    double** Ab = mat_cria(n, n+1);
    
    // Copy the augmented matrix [A|b]
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Ab[i][j] = A[i][j];
        }
        Ab[i][n] = b[i];
    }
    
    // Gaussian elimination
    for (int k = 0; k < n-1; k++) {
        // Find the maximum pivot in column k
        int max_row = k;
        for (int i = k+1; i < n; i++) {
            if (fabs(Ab[i][k]) > fabs(Ab[max_row][k])) {
                max_row = i;
            }
        }
        
        // Swap rows if necessary
        if (max_row != k) {
            for (int j = k; j <= n; j++) {
                double temp = Ab[k][j];
                Ab[k][j] = Ab[max_row][j];
                Ab[max_row][j] = temp;
            }
        }
        
        // Check if pivot is zero (singular matrix)
        if (fabs(Ab[k][k]) < 1e-15) {
            // Handle singular matrix case
            // In this case, we'll continue but the result may be inaccurate
            continue;
        }
        
        // Elimination
        for (int i = k+1; i < n; i++) {
            double factor = Ab[i][k] / Ab[k][k];
            for (int j = k; j <= n; j++) {
                Ab[i][j] -= factor * Ab[k][j];
            }
        }
    }
    
    // Back substitution
    for (int i = n-1; i >= 0; i--) {
        x[i] = Ab[i][n];
        for (int j = i+1; j < n; j++) {
            x[i] -= Ab[i][j] * x[j];
        }
        if (fabs(Ab[i][i]) > 1e-15) {
            x[i] /= Ab[i][i];
        } else {
            x[i] = 0.0; // Avoid division by zero
        }
    }
    
    mat_libera(n, Ab);
}