#include <stdio.h>
#include <stdlib.h>
#include "rtbp.h"
#include "zeros.h"

#define MU 1.215058560962404e-2
#define PMAX .01

struct estructura {
   double c;
   int isgn;
};

double lyap_bis_fdf (double x, void *prm) {
   struct estructura *params=prm;
   double u;
   proptraj(MU, 1, params->c, params->isgn, x, &u, NULL, PMAX, NULL);
   return u;
}


void lyap_nwt_fdf (double x, double *v, double *dv, void *prm) {
   struct estructura *params=prm;
   proptraj(MU, 1, params->c, params->isgn, x, v, dv, PMAX, NULL);
}


int main(int argc, char *argv[]){
   double c, xa, xb, tolbis, tolfnwt;
   int isgn, maxitnwt, ixrr;

/*
 * Línia de comandes
   double c int isgn double xa double xb double tolbis double tolfnwt int maxitnwt int ixrr
 */
   if (argc<9
         || sscanf(argv[1], "%lf", &c)!=1
         || sscanf(argv[2], "%d", &isgn)!=1
         || sscanf(argv[3], "%lf", &xa)!=1
         || sscanf(argv[4], "%lf", &xb)!=1
         || sscanf(argv[5], "%lf", &tolbis)!=1
         || sscanf(argv[6], "%lf", &tolfnwt)!=1
         || sscanf(argv[7], "%d", &maxitnwt)!=1
         || sscanf(argv[8], "%d", &ixrr)!=1
      ) {
      fprintf(stderr,"%s c isgn xa xb tolbis tolfnwt maxitnwt ixrr \
\n\
", argv[0]);
      return -1;
   }
/*
 * Fi línia de comandes
 */
   struct estructura prm;
   prm.c=c; prm.isgn=isgn;

   // comencem fent bisecció
   double x_lyp = biseccio(&xa, &xb, tolbis, lyap_bis_fdf, &prm, ixrr);

   // fem newton a partir de x_lyp
   newton(&x_lyp, tolfnwt, 0, maxitnwt, lyap_nwt_fdf, &prm, ixrr);
   printf("x = %.16g \n", x_lyp);

   return 0;
}
