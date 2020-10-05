#ifndef _def_h_
#define _def_h_

#define ALIGN 64

#define ERR_ARG 1
#define ERR_PTR 2

#define MAX_N RAND_MAX

#define ITE 500

typedef struct rdp_s
{
  int n;
  double *a;
  double *b;
  double *c;
}* rdp_t;

#endif //!_def_h_
