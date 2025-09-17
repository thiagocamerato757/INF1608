#include "sistlinear.h"
#include "matriz.h"
#include "vetor.h"
#include <stdio.h>
#include <stdlib.h>

static void avaliagauss (int n, double **A, double* b)
{
  printf("Matriz A e vetor b:\n");
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      printf("%10.4f ", A[i][j]);
	}
    printf(" - %10.4f\n", b[i]);
  }
  double* x = vet_cria(n);
  
  gauss(n, A, b, x);
  
  printf("Vetor X:\n");
  for (int i = 0; i < n; ++i) {
    printf("%10.15f", x[i]);
	if (i < n-1) printf(", ");
  }
  printf("\n");
  printf("------------------------------------------------\n");
  vet_libera(x);
}

static void trocalinha (int n, double **A, double* b, int L0, int L1)
{
  for (int i = 0; i < n; ++i) {
    double AvL0 = A[L0][i];
    A[L0][i] = A[L1][i];
    A[L1][i] = AvL0;
  }
  double bvL0 = b[L0];
  b[L0] = b[L1];
  b[L1] = bvL0;
}

int main (void)
{
  {
    double** A1 = mat_cria(3,3);
    A1[0][0] =  1; A1[0][1] = -1; A1[0][2] = 0;
    A1[1][0] = -1; A1[1][1] =  2; A1[1][2] = 1;
    A1[2][0] =  0; A1[2][1] =  1; A1[2][2] = 2;
    double* B1 = vet_cria(3);
    B1[0] = 0; B1[1] = 2; B1[2] = 3;
    avaliagauss(3, A1, B1);
    mat_libera(3, A1);
    vet_libera(B1);
  }

  {
    double** A2 = mat_cria(6,6);
    A2[0][0] =   3; A2[0][1] =  -1; A2[0][2] =  0; A2[0][3] =  0; A2[0][4] =   0; A2[0][5] = 0.5;
    A2[1][0] =  -1; A2[1][1] =   3; A2[1][2] = -1; A2[1][3] =  0; A2[1][4] = 0.5; A2[1][5] =   0;
    A2[2][0] =   0; A2[2][1] =  -1; A2[2][2] =  3; A2[2][3] = -1; A2[2][4] =   0; A2[2][5] =   0;
    A2[3][0] =   0; A2[3][1] =   0; A2[3][2] = -1; A2[3][3] =  3; A2[3][4] =  -1; A2[3][5] =   0;
    A2[4][0] =   0; A2[4][1] = 0.5; A2[4][2] =  0; A2[4][3] = -1; A2[4][4] =   3; A2[4][5] =  -1;
    A2[5][0] = 0.5; A2[5][1] =   0; A2[5][2] =  0; A2[5][3] =  0; A2[5][4] =  -1; A2[5][5] =   3;
    double* B2 = vet_cria(6);
    B2[0] = 2.5; B2[1] = 1.5; B2[2] = 1; B2[3] = 1; B2[4] = 1.5; B2[5] = 2.5;
    avaliagauss(6, A2, B2);
    mat_libera(6, A2);
    vet_libera(B2);
  }

  {
    double** A = mat_cria(2,2);
    A[0][0] = 1;      A[0][1] = 1;
    A[1][0] = 1.0001; A[1][1] = 1;
    double b[2] = {2,2.0001};
    avaliagauss(2,A,b);
    mat_libera(2, A);
  }
  
  {
    double** A = mat_cria(2,2);
    A[0][0] = -2; A[0][1] = 1;
    A[1][0] =  1; A[1][1] = 2;
    double b[2] = {2,3};
    avaliagauss(2,A,b);
    mat_libera(2, A);
  }

  {
    double** A2 = mat_cria(6,6);
    A2[0][0] =   3; A2[0][1] =  -1; A2[0][2] =  0; A2[0][3] =  0; A2[0][4] =   0; A2[0][5] = 0.5;
    A2[1][0] =  -1; A2[1][1] =   3; A2[1][2] = -1; A2[1][3] =  0; A2[1][4] = 0.5; A2[1][5] =   0;
    A2[2][0] =   0; A2[2][1] =  -1; A2[2][2] =  3; A2[2][3] = -1; A2[2][4] =   0; A2[2][5] =   0;
    A2[3][0] =   0; A2[3][1] =   0; A2[3][2] = -1; A2[3][3] =  3; A2[3][4] =  -1; A2[3][5] =   0;
    A2[4][0] =   0; A2[4][1] = 0.5; A2[4][2] =  0; A2[4][3] = -1; A2[4][4] =   3; A2[4][5] =  -1;
    A2[5][0] = 0.5; A2[5][1] =   0; A2[5][2] =  0; A2[5][3] =  0; A2[5][4] =  -1; A2[5][5] =   3;
    double* B2 = vet_cria(6);
    B2[0] = 2.5; B2[1] = 1.5; B2[2] = 1; B2[3] = 1; B2[4] = 1.5; B2[5] = 2.5;
	  trocalinha(6, A2, B2, 0, 2);
    trocalinha(6, A2, B2, 1, 4);
    avaliagauss(6, A2, B2);
    mat_libera(6, A2);
    vet_libera(B2);
  }

  {
    double** A = mat_cria(3,3);
    A[0][0] = -3; A[0][1] =  1; A[0][2] =  1;
    A[1][0] =  2; A[1][1] =  1; A[1][2] = -2;
    A[2][0] =  1; A[2][1] =  2; A[2][2] = -1;
    double* b = vet_cria(3);
    b[0] = -6; b[1] = 3; b[2] = 3;
    avaliagauss(3, A, b);
    mat_libera(3, A);
    vet_libera(b);
  }

  {
    double** A = mat_cria(3,3);
    A[0][0] = -3; A[0][1] =  1; A[0][2] =  1;
    A[1][0] =  2; A[1][1] =  1; A[1][2] = -2;
    A[2][0] =  1; A[2][1] =  2; A[2][2] = -1;
    double* b = vet_cria(3);
    b[0] = -6; b[1] = 3; b[2] = 3;
    trocalinha(3, A, b, 0, 2);
    avaliagauss(3, A, b);
    mat_libera(3, A);
    vet_libera(b);
  }

  {
    double** A = mat_cria(2,2);
    A[0][0] = 1e-17; A[0][1] = 1;
    A[1][0] =     1; A[1][1] = 2;
    double b[2] = {1,4};
    avaliagauss(2,A,b);
    mat_libera(2, A);
  }

  return 0;
}

