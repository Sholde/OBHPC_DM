#ifndef _rdc_h_
#define _rdc_h_

#include "rdtsc.h"

//Init rdp_t with random value
void rdp_t_init(rdp_t m)
{
  if (!m || !m->a || !m->b || !m->c)
    printf("Error: pointer cannot be NULL\n"), exit(ERR_PTR);
  
  for(int i = 0; i < m->n; i++)
    {
      for(int j = 0; j < m->n; j++)
	{
	  m->a[i * m->n + j] = rand_double();
	  m->b[i * m->n + j] = rand_double();
	  m->c[i * m->n + j] = 0;
	}
    }
}

//Print rdp_t on standard output
void rdp_t_print(FILE *fd, const rdp_t m)
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
void print_perf(const char *str, int size, double cy, int set)
{
  if (!set)
    printf("\033[1;34mSize = %d\033[0m\n", size);
  
  printf("%s\t%lf\tcycles(average)\n", str, cy);
  printf("\n");
}

//Write the C matrix on file
void rdp_t_write(const char *fname, const rdp_t m)
{
  if (!fname)
    printf("Error: NULL pointer!\n"), exit(ERR_PTR);

  FILE *fd = fopen(fname, "w");

  if (!fd)
    printf("Error: NULL pointer!\n"), exit(ERR_PTR);

  rdp_t_print(fd, m);

  fclose(fd);
}

//Alloc memory
rdp_t rdp_t_alloc(const unsigned int n)
{
  rdp_t m = aligned_alloc(ALIGN, sizeof(struct rdp_s));

  if (!m)
    return printf("Error: cannot allocate memory\n"), NULL;

  m->n = n;
  m->a = aligned_alloc(n, sizeof(double) * n * n);
  m->b = aligned_alloc(n, sizeof(double) * n * n);
  m->c = aligned_alloc(n, sizeof(double) * n * n);
  
  if (!m->a || !m->b || !m->c)
    return printf("Error: cannot allocate memory\n"), NULL;
  
  return m;
}

//Free memory
void rdp_t_free(rdp_t m)
{
  if (!m || !m->a || !m->b || !m->c)
    printf("Error: pointer cannot be NULL\n"), exit(ERR_PTR);

  memset(m->a, 0, m->n * m->n);
  free(m->a);
  memset(m->b, 0, m->n * m->n);
  free(m->b);
  memset(m->c, 0, m->n * m->n);
  free(m->c);
  
  free(m);
}

//Compute
void rdp_t_compute_1(rdp_t m)
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

void rdp_t_compute_2(rdp_t m)
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

//test
void rdp_t_compute_3(rdp_t m)
{
  double *tmp = malloc(sizeof(double) * m->n * m->n);
  for (int i = 0; i < m->n; i++)
    {
      for (int j = 0; j < m->n; j++)
	{
	  tmp[i * m->n + j] = m->a[i * m->n + j] * m->b[j * m->n + i];
	}
    }

  for (int i = 0; i < m->n; i++)
    {
      for (int j = 0; j < m->n; j++)
	m->c[i * m->n + j] += tmp[i * m->n + j] + tmp[j * m->n +i];
    }
  
  free(tmp);
}

//Check pointer
void rdp_t_pointer_check(rdp_t m)
{
  if (!m || !m->a || !m->b || !m->c)
    printf("Error: pointer cannot be NULL!\n"), exit(ERR_PTR);
}

//
void rdp_t_compute(rdp_t m)
{
  rdp_t_pointer_check(m);
  
  rdp_t tmp = rdp_t_alloc(m->n);
  for (int i = 0; i < tmp->n; i++)
    {
      for (int j = 0; j < tmp->n; j++)
	{
	  tmp->a[i * tmp->n + j] = m->a[i * m->n + j];
	  tmp->b[i * tmp->n + j] = m->b[i * m->n + j];
	  tmp->c[i * tmp->n + j] = m->c[i * m->n + j];
	}
    }

  int set = 0;
  double before, after, t, cycles1, cycles2, cpr1, cpr2, speedup;
  
  // loop i -> j -> k
  for (int i = 0; i < ITE; i++)
    {
      do
	{
	  before = rdtsc();
      
	  rdp_t_compute_1(m);

	  after = rdtsc();

	  t = after - before;
	}
      while (cycles1 < 0);

      cycles1 += t;

      memset(m->c, 0, m->n * m->n);
    }
  
  cpr1 = cycles1 / ITE;

  char str1[] = "i->j->k";
  print_perf(str1, m->n, cpr1, set);

  // loop i -> k -> j
  set = 1;
  
  for (int i = 0; i < ITE; i++)
    {
      do
	{
	  before = rdtsc();
      
	  rdp_t_compute_2(tmp);

	  after = rdtsc();

	  t = after - before;
	}
      while (cycles2 < 0);

      cycles2 += t;

      memset(tmp->c, 0, tmp->n * tmp->n);
    }
    
  

  cpr2 = cycles2 / ITE;

  char str2[] = "i->k->j";
  print_perf(str2, m->n, cpr2, set);

  speedup = cpr1 / cpr2;
  
  if (speedup >= 1)
    printf("\033[1;32mSpeedup : %lf\033[0m\n\n", speedup);
  else
    printf("\033[1;31mSpeedup : %lf\033[0m\n\n", speedup);
}

#endif //!_rdc_h_
