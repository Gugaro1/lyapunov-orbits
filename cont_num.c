#include <stdio.h>
#include <stdlib.h>
#include "rtbp.h"
#include "zeros.h"
#include <math.h>

#define MU 1.215058560962404e-2
#define PMAX .1

struct estructura {
   double c;
   int isgn;
};

void lyap_nwt_fdf (double x, double *v, double *dv, void *prm) {
   struct estructura *params=prm;
   proptraj(MU, 1, params->c, params->isgn, x, v, dv, PMAX, NULL);
}

int main(int argc, char *argv[]){
   double x0, c0, l_max, l_step, tolfnwt;
   int isgn, maxitnwt, ixrr;
   if (argc<9
         || sscanf(argv[1], "%d", &isgn)!=1
         || sscanf(argv[2], "%lf", &x0) !=1
         || sscanf(argv[3], "%lf", &c0) !=1
         || sscanf(argv[4], "%lf", &l_max)!=1
         || sscanf(argv[5], "%lf", &l_step)!=1
         || sscanf(argv[6], "%lf", &tolfnwt)!=1
         || sscanf(argv[7], "%d", &maxitnwt)!=1
         || sscanf(argv[8], "%d", &ixrr)!=1
      ) {
      fprintf(stderr,"%s isgn x0 c0 l_max l_step tolfnwt maxitnwt ixrr \
\n\
", argv[0]);
      return -1;
   }

    
   struct estructura prm;
   prm.c=c0; prm.isgn=isgn;
   int i = 0;
   while(i*l_step < l_max){
      i++;
      prm.c = prm.c - l_step;
      double xi = newton(&x0, tolfnwt, 0, maxitnwt, lyap_nwt_fdf, &prm, ixrr);
      if (xi != -1) {
         printf("x = %.16g, c = %.16g\n", x0, prm.c);
      }   
   }
   return 0;
}