#ifndef _rdc_h_
#define _rdc_h_

#include "rdtsc.h"

//Init rdc_t with random value
void rdc_t_init(rdc_t m)
{
  if (!m || !m->a || !m->b || !m->c)
    printf("Error: pointer cannot be NULL\n"), exit(ERR_PTR);
  
  for(int i = 0; i < m->n; i++)
    {
      for(int j = 0; j < m->n; j++)
	{
	  m->a[i * m->n + j] = rand_double();
	  m->b[i * m->n + j] = rand_double();
	  m->c[i * m->n + j] = rand_double();
	}
    }
}

//Print rdc_t on standard output
void rdc_t_print(FILE *fd, const rdc_t m)
{
  if (!fd || !m || !m->a || !m->b || !m->c)
    printf("Error: pointer cannot be NULL\n"), exit(ERR_PTR);
  
  fprintf(fd, "n = %d\n", m->n);
  
  for (int i = 0; i < m->n; i++)
    {
      for (int j = 0; j < m->n; j++)
	{
	  fprintf(fd, "%lf ", m->c[i * m->n + j]);
	}
      fprintf(fd, "\n");
    }
}

//Print performance
void print_perf(int n, double p)
{
  printf("Size = %d\n", n);
  printf("Cycles = %lf\n", p);
}

//Alloc memory
rdc_t rdc_t_alloc(const unsigned int n)
{
  rdc_t m = aligned_alloc(ALIGN, sizeof(struct rdc_s));

  if (!m)
    return printf("Error: cannot allocate memory\n"), NULL;

  m->n = n;
  m->a = aligned_alloc(ALIGN, sizeof(double) * n * n);
  m->b = aligned_alloc(ALIGN, sizeof(double) * n * n);
  m->c = aligned_alloc(ALIGN, sizeof(double) * n * n);
  
  if (!m->a || !m->b || !m->c)
    return printf("Error: cannot allocate memory\n"), NULL;
  
  return m;
}

//Free memory
void rdc_t_free(rdc_t m)
{
  if (!m || !m->a || !m->b || !m->c)
    printf("Error: pointer cannot be NULL\n"), exit(ERR_PTR);
  
  free(m->a);
  free(m->b);
  free(m->c);
  
  free(m);
}

//Compute
void rdc_t_compute_1(rdc_t m)
{
  for (int i = 0; i < m->n; i++)
    {
      for (int j = 0; j < m->n; j++)
	{
	  for (int k = 0; k < m->n; k++)
	    {
	      m->c[i * m->n + j] += m->a[i * m->n + k] * m->b[k * m->n + j];
	    }
	}
    }
}

void rdc_t_compute_2(rdc_t m)
{
  for (int i = 0; i < m->n; i++)
    {
      for (int k = 0; k < m->n; k++)
	{
	  for (int j = 0; j < m->n; j++)
	    {
	      m->c[i * m->n + j] += m->a[i * m->n + k] * m->b[k * m->n + j];
	    }
	}
    }
}

//Check pointer
void rdc_t_pointer_check(rdc_t m)
{
  if (!m || !m->a || !m->b || !m->c)
    printf("Error: pointer cannot be NULL!\n"), exit(ERR_PTR);
}

//
void rdc_t_compute(rdc_t m)
{
  rdc_t_pointer_check(m);

  double before, after, cycles1, cycles2, cpr1, cpr2, speedup;
  
  // loop i -> j -> k
  before = rdtsc();
  
  for (int i = 0; i < ITE; i++)
    {
      rdc_t_compute_1(m);
    }
  
  after = rdtsc();
  
  cycles1 = after - before;

  cpr1 = cycles1 / ITE;

  printf("\033[1;34mi->j->k loop (%d iterations) :\033[0m\n", ITE);
  print_perf(m->n, cpr1);
  printf("\n");

  // loop i -> k -> j
  before = rdtsc();
  
  for (int i = 0; i < ITE; i++)
    {
      rdc_t_compute_2(m);
    }
  
  after = rdtsc();
  
  cycles2 = after - before;

  cpr2 = cycles2 / ITE;
  printf("\033[1;34mi->k->j loop (%d iterations) :\033[0m\n", ITE);
  print_perf(m->n, cpr2);
  printf("\n");

  speedup = cpr1 / cpr2;
  if (speedup >= 1)
    printf("\033[1;32mSpeedup : %lf\033[0m\n\n", speedup);
  else
    printf("\033[1;31mSpeedup : %lf\033[0m\n\n", speedup);
}

//Write the rdc_t C on file
void rdc_t_write(const char *fname, const rdc_t m)
{
  if (!fname)
    printf("Error: NULL pointer!\n"), exit(ERR_PTR);

  FILE *fd = fopen(fname, "w");

  if (!fd)
    printf("Error: NULL pointer!\n"), exit(ERR_PTR);

  rdc_t_print(fd, m);

  fclose(fd);
}

#endif //!_rdc_h_
