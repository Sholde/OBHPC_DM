#ifndef _rdp_h_
#define _rdp_h_

#include "rdtsc.h"

//Alloc memory
double *matrix_alloc(const int size)
{
  double *m = aligned_alloc(size, sizeof(double) * size * size);

  if (!m)
    return printf("Error: cannot allocate memory\n"), NULL;

  memset(m, 0, size * size);
  
  return m;
}

//Free memory
void matrix_free(const int size, double *m)
{
  if (!m)
    printf("Error: pointer cannot be NULL\n"), exit(ERR_PTR);

  memset(m, 0, size * size);

  free(m);
}


//Init matrix with random value
void matrix_init_random(const int size, double *m)
{
  if (!m)
    printf("Error: pointer cannot be NULL\n"), exit(ERR_PTR);
  
  for(int i = 0; i < size * size; i++)
    {
      m[i] = rand_double();
    }
}

//Init matrix with Integer value
void matrix_init_integer(const int size, const int val, double *m)
{
  if (!m)
    printf("Error: pointer cannot be NULL\n"), exit(ERR_PTR);
  
  for(int i = 0; i < size * size; i++)
    {
      m[i] = val;
    }
}

//Print matrix on standard output
void matrix_print(FILE *fd, const int size, const double *m)
{
  if (!fd || !m)
    printf("Error: pointer cannot be NULL\n"), exit(ERR_PTR);
  
  fprintf(fd, "%d\n", size);
  
  for (int i = 0; i < size; i++)
    {
      for (int j = 0; j < size; j++)
	{
	  fprintf(fd, "%lf ", m[i * size + j]);
	}
      fprintf(fd, "\n");
    }
}

//Print performance
void print_perf(const char *str, const int size, const double cy, const int set)
{
  if (!set)
    printf("\033[1;34mSize = %d\033[0m\n", size);
  
  printf("%s\t%lf\tcycles(average)\n", str, cy);
  printf("\n");
}

//Write the C matrix on file
void matrix_write(const char *fname, const int size, const double *m)
{
  if (!fname || !m)
    printf("Error: NULL pointer!\n"), exit(ERR_PTR);

  FILE *fd = fopen(fname, "w");

  if (!fd)
    printf("Error: NULL pointer!\n"), exit(ERR_PTR);

  matrix_print(fd, size, m);

  fclose(fd);
}

double *matrix_read(const char *fname, const int size)
{
  if (!fname)
    printf("Error: NULL pointer!\n"), exit(ERR_PTR);

  FILE *fd = fopen(fname, "r");

  if (!fd)
    printf("Error: NULL pointer!\n"), exit(ERR_PTR);

  int tmp_size = 0;
  fscanf(fd, "%d", &tmp_size);

  if (tmp_size != size)
    return NULL;

  double *m = matrix_alloc(size);

  for (int i = 0; i < size * size; i++)
    {
      fscanf(fd, "%lf", &m[i]);
    }

  fclose(fd);

  return m;
}

//Compute
void matrix_compute_1(const int size, double *c, const double *a, const double *b)
{
  for (int i = 0; i < size; i++)
    {
      for (int j = 0; j < size; j++)
	{
	  for (int k = 0; k < size; k++)
	    {
	      c[i * size + j] += a[i * size + k] * b[k * size + j];
	    }
	}
    }
}

void matrix_compute_2(const int size, double *c, const double *a, const double *b)
{
  for (int i = 0; i < size; i++)
    {
      for (int k = 0; k < size; k++)
	{
	  for (int j = 0; j < size; j++)
	    {
	      c[i * size + j] += a[i * size + k] * b[k * size + j];
	    }
	}
    }
}

//test
/*
void rdp_t_compute_3(rdp_t m)
{
  double *tmp = malloc(sizeof(double) * size * size);
  for (int i = 0; i < size; i++)
    {
      for (int j = 0; j < size; j++)
	{
	  tmp[i * size + j] = m[i * size + j] * m[j * size + i];
	}
    }

  for (int i = 0; i < size; i++)
    {
      for (int j = 0; j < size; j++)
	m[i * size + j] += tmp[i * size + j] + tmp[j * size +i];
    }
  
  free(tmp);
}
*/

//
void matrix_compute(const int size, double *c, const double *a, const double *b)
{
  int set = 0;
  double before, after, t, cycles1, cycles2, cpr1, cpr2, speedup;
  
  // loop i -> j -> k
  for (int i = 0; i < ITE; i++)
    {
      do
	{
	  before = rdtsc();
      
	  matrix_compute_1(size, c, a, b);

	  after = rdtsc();

	  t = after - before;
	}
      while (cycles1 < 0);

      cycles1 += t;

      memset(c, 0, size * size);
    }
  
  cpr1 = cycles1 / ITE;

  char str1[] = "i->j->k";
  print_perf(str1, size, cpr1, set);

  // loop i -> k -> j
  set = 1;
  
  for (int i = 0; i < ITE; i++)
    {
      do
	{
	  before = rdtsc();
      
	  matrix_compute_2(size, c, a, b);

	  after = rdtsc();

	  t = after - before;
	}
      while (cycles2 < 0);

      cycles2 += t;

      memset(c, 0, size * size);
    }
    
  

  cpr2 = cycles2 / ITE;

  char str2[] = "i->k->j";
  print_perf(str2, size, cpr2, set);

  speedup = cpr1 / cpr2;
  
  if (speedup >= 1)
    printf("\033[1;32mSpeedup : %lf\033[0m\n\n", speedup);
  else
    printf("\033[1;31mSpeedup : %lf\033[0m\n\n", speedup);
}

#endif //!_rdp_h_
