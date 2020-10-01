#ifndef _def_h_
#define _def_h_

#define ALIGN 64

#define ERR_ARG 1
#define ERR_PTR 2

#define MAX_N RAND_MAX

typedef struct rdc_s
{
  int n;
  double **a;
  double **b;
  double **c;
}* rdc_t;

#endif //!_def_h_