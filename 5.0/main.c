#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ALIGN 64

#define ERR_ARG 1
#define ERR_PTR 2

#define MAX_N RAND_MAX

typedef struct static_matrix
{
  int n;
  double **a;
  double **b;
  double **c;
}* matrix;

//typedef struct static_matrix * matrix;

//Init random seed
static inline void init_seed()
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

//Init matrix with random value
void init_matrix(matrix m)
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

//Print matrix on standard output
void print_matrix(FILE *fd, const matrix m)
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
matrix alloc_matrix(const unsigned int n)
{
  matrix m = aligned_alloc(ALIGN, sizeof(struct static_matrix));

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
void free_matrix(matrix m)
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
void compute_matrix_(matrix m)
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
void matrix_pointer_check(matrix m)
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
void compute_matrix(matrix m)
{
  matrix_pointer_check(m);
  compute_matrix_(m);
}

//Write the matrix C on file
void write_matrix(const char *fname, const matrix m)
{
  if (!fname)
    printf("Error: NULL pointer!\n"), exit(ERR_PTR);

  FILE *fd = fopen(fname, "w");

  if (!fd)
    printf("Error: NULL pointer!\n"), exit(ERR_PTR);

  print_matrix(fd, m);

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
  matrix m = alloc_matrix(n);
  
  //Initialisation
  init_seed();
  init_matrix(m);
  
  //Compute
  compute_matrix(m);

  //Print
  write_matrix(argv[2], m);

  //Free memory
  free_matrix(m);
  
  return 0;
}
