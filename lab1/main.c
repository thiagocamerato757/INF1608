#include "taylor.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.141592653589793

const char* atostring (int i)
{
  switch(i) {
  case 0:
    return "PI/12.0";
    break;
  case 1:
    return "PI/9.0";
    break;
  case 2:
    return "PI/7.0";
    break;
  case 3:
    return "PI/4.0";
    break;
  case 4:  
    return "PI/3.0";
    break;
  };
}

int main (void)
{
  double a[5] = {PI/12.0, PI/9.0, PI/7.0, PI/4.0, PI/3.0};
  
  printf("\nSeno:\n");
  for (int i=0; i<5; ++i) {
    double v = sin(a[i]);
    printf("\nTeste avalia_seno com x = %s, onde o valor exato sen(%s) = %.10f\n", atostring(i), atostring(i),v);
    for (int n=1; n<=10; ++n) {
      double v1 = avalia_seno(n,a[i]);
      double d = v-v1;
      printf("Para n = %d: avalia_seno = %.10f e diferenca do valor exato = %.10f\n",n,v1,d);
    }
  }
  return 0;
}
