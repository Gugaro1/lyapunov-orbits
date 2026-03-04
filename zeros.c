#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double biseccio (double *a, double *b, double tol, double (*f)(double,void*), void *prm, int ixrr) {
      double p = *a;
      double k = *b-*a;
      int i = 1;
      while(k > tol){
            p = (*a + *b)/2;
            if((f)(*a, prm )*(f)(p, prm) <= 0){
                  *b = p;
            }
            else{
                  *a = p;
            }
            k = k/2;
            if(ixrr == 1){
                  printf("p%d = %.16g \n", i, p);
            }
            i++;
      }
      return p = (*a + *b)/2;
}

int newton (double *x, double tolf, double tolx, int maxit, void (*fdf)(double,double*,double*,void*), void *prm, int ixrr){
      double xi, fx, dfx;
      fdf(*x, &fx, &dfx, prm);
      for(int i = 1; i <= maxit; i++){
            xi = *x;
            *x = *x - fx/(dfx);
            fdf(*x, &fx, &dfx, prm);
            if(ixrr == 1){
                  printf("x%d = %.16g \n", i, *x);
            }
            if((fabs(fx) <= tolf) && (fabs(*x - xi) <= tolx)){
                  return i;
            }
      }
  return -1;    
}
