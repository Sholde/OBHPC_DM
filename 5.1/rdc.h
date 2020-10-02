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
      if (!m->a[i] || !m->b[i] || !m->c[i])
	printf("Error: pointer cannot be NULL\n"), exit(ERR_PTR);
      
      for(int j = 0; j < m->n; j++)
	{
	  m->a[i][j] = rand_double();
	  m->b[i][j] = rand_double();
	  m->c[i][j] = rand_double();
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
      if (!m->a[i] || !m->b[i] || !m->c[i])
	printf("Error: pointer cannot be NULL\n"), exit(ERR_PTR);
      
      for (int j = 0; j < m->n; j++)
	{
	  fprintf(fd, "%lf ", m->c[i][j]);
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
  m->a = aligned_alloc(ALIGN, sizeof(double *) * n);
  m->b = aligned_alloc(ALIGN, sizeof(double *) * n);
  m->c = aligned_alloc(ALIGN, sizeof(double *) * n);
  
  for (int i = 0; i < m->n; i++)
    {
      m->a[i] = aligned_alloc(ALIGN, sizeof(double) * n);
      m->b[i] = aligned_alloc(ALIGN, sizeof(double) * n);
      m->c[i] = aligned_alloc(ALIGN, sizeof(double) * n);

      if (!m->a[i] || !m->b[i] || !m->c[i])
	return printf("Error: cannot allocate memory\n"), NULL;
    }
  
  return m;
}

//Free memory
void rdc_t_free(rdc_t m)
{
  if (!m || !m->a || !m->b || !m->c)
    printf("Error: pointer cannot be NULL\n"), exit(ERR_PTR);
  
  for (int i = 0; i < m->n; i++)
    {
      if (!m->a[i] || !m->b[i] || !m->c[i])
	printf("Error: pointer cannot be NULL\n"), exit(ERR_PTR);
      free(m->a[i]);
      free(m->b[i]);
      free(m->c[i]);
    }

  free(m->a);
  free(m->b);
  free(m->c);
  
  free(m);
}

//Compute
void rdc_t_compute_(rdc_t m)
{
  for (int i = 0; i < m->n; i++)
    {
      for (int j = 0; j < m->n; j++)
	{
	  for (int k = 0; k < m->n; k++)
	    {
	      m->c[i][j] += m->a[j][k] * m->b[k][j];
	    }
	}
    }
}

//Check pointer
void rdc_t_pointer_check(rdc_t m)
{
  if (!m || !m->a || !m->b || !m->c)
    printf("Error: pointer cannot be NULL!\n"), exit(ERR_PTR);
  
  for (int i = 0; i < m->n; i++)
    {
      if(!m->a[i] || !m->b[i] || !m->c[i])
	printf("Error: pointer cannot be NULL!\n"), exit(ERR_PTR);
    }
}

//
void rdc_t_compute(rdc_t m)
{
  rdc_t_pointer_check(m);

  double before = rdtsc();
  
  rdc_t_compute_(m);
  
  double after = rdtsc();

  double cycles = after - before;
  
  print_perf(m->n, cycles);
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
