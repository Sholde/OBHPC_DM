#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

//Init random seed
static inline void seed_init()
{
  srand(time(NULL));
}

//Random sign function
static inline char rand_sign()
{
  return (rand() & 1) ? 1 : -1;
}

//Random int function
static inline double rand_double()
{
  return (double)rand() / (double)rand() * rand_sign();
}

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
  rdc_t_compute_(m);
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

//Main function
int main(int argc, char **argv)
{
  //Check argument
  if (argc != 3)
    return printf("Usage: %s [size] [output file]\n", argv[0]), ERR_ARG;
  
  int n = atoi(argv[1]);
  if (n <= 0)
    return printf("You must use a positive number\n"), ERR_ARG;
  if (n > MAX_N)
    return printf("You must enter a number <= %d\n", MAX_N);

  //Alloction
  rdc_t m = rdc_t_alloc(n);
  
  //Initialisation
  seed_init();
  rdc_t_init(m);
  
  //Compute
  rdc_t_compute(m);

  //Print
  rdc_t_write(argv[2], m);

  //Free memory
  rdc_t_free(m);
  
  return 0;
}
