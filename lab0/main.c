#include "vetor.h"
#include "matriz.h"
#include <stdio.h>

int main (void)
{
  /* Exemplo de construção de vetor dinâmico */
  double* v = vet_cria(2);
  v[0] = 1.0;
  v[1] = 2.0;

  /* Exemplo de construção de vetor estático */
  double w[] = {1.0,2.0f};

  /* Imprime vetores (são iguais em conteúdo) */
  vet_imprime(2,v);
  vet_imprime(2,w);

  /* Exemplo de construção de matriz dinâmica */
  double** A = mat_cria(3,2);
  A[0][0] = 1.0;
  A[0][1] = 2.0;
  A[1][0] = 3.0;
  A[1][1] = 4.0;
  A[2][0] = 5.0;
  A[2][1] = 6.0;

  /* Exemplo de construção de matriz estática no formato ponteiro para ponteiro */
  double linha1[] = {1.0,2.0};
  double linha2[] = {3.0,4.0};
  double linha3[] = {5.0,6.0};
  double* B[] = {linha1,linha2,linha3};
  double escalar;
  double norma;

  /* Imprime matrizes (são iguais em conteúdo) */
  mat_imprime(3,2,A);
  mat_imprime(3,2,B);


  escalar = vet_escalar(2,v,w);
  printf("\nproduto escalar: %.16g\n",escalar);
  norma = vet_norma2(2,v);
  printf("\nnorma do vetor: %.16g\n",norma);

  printf("\nvetores %siguais\n", vet_iguais(2,v,w,0) ? "" : "não ");

  /* ==================== TESTES ADICIONAIS ==================== */
  
  printf("\n=== TESTANDO TRANSPOSTA ===\n");
  double** T = mat_cria(2,3);
  mat_transposta(3,2,A,T);
  printf("Matriz original A:\n");
  mat_imprime(3,2,A);
  printf("Transposta T:\n");
  mat_imprime(2,3,T);

  printf("\n=== TESTANDO MULTIPLICAÇÃO MATRIZ-VETOR ===\n");
  double* resultado = vet_cria(3);
  mat_multv(3,2,A,v,resultado);
  printf("A × v = ");
  vet_imprime(3,resultado);

  printf("\n=== TESTANDO MULTIPLICAÇÃO MATRIZ-MATRIZ ===\n");
  double** C = mat_cria(3,3);
  double** B_mult = mat_cria(2,3);
  B_mult[0][0] = 1.0; B_mult[0][1] = 0.0; B_mult[0][2] = -1.0;
  B_mult[1][0] = 0.0; B_mult[1][1] = 1.0; B_mult[1][2] = 2.0;
  
  mat_multm(3,2,3,A,B_mult,C);
  printf("A × B_mult =\n");
  mat_imprime(3,3,C);

  printf("\n=== TESTE COM TOLERÂNCIA ===\n");
  double v_aprox[] = {1.0001, 1.9999};
  printf("v aproximado com tolerância 0.01: %siguais\n", 
         vet_iguais(2,v,v_aprox,0.01) ? "" : "não ");

  /* Apenas objetos dinâmicos podem ser liberados */
  vet_libera(v);
  vet_libera(resultado);
  mat_libera(3,A);
  mat_libera(2,T);
  mat_libera(2,B_mult);
  mat_libera(3,C);

  return 0; 
}