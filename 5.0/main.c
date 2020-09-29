#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ALIGN 64

#define ERR_ARG 1
#define ERR_PTR 2

#define MAX_N 100

//Init random seed
static inline void init_seed()
{
  srand(time(NULL));
}

//Random sign function
static inline char rand_sign(const char x, const char y)
{
  return (((rand() % (y - x + 1)) + x) ? 1 : -1);
}

//Random int function
static inline double rand_double()
{
  return (double)(rand() % RAND_MAX) / (double)(rand() % RAND_MAX) * rand_sign(0, 1);
}

//Init matrix with random value
void init_matrix(int n, double **a, double **b, double **c)
{
  if (!a)
    printf("Error: pointer cannot be NULL\n"), exit(ERR_PTR);
  if (!b)
    printf("Error: pointer cannot be NULL\n"), exit(ERR_PTR);
  if (!c)
    printf("Error: pointer cannot be NULL\n"), exit(ERR_PTR);
  
  for(int i = 0; i < n; i++)
    {
      if (!a[i])
	printf("Error: pointer cannot be NULL\n"), exit(ERR_PTR);
      if (!b[i])
	printf("Error: pointer cannot be NULL\n"), exit(ERR_PTR);
      if (!c[i])
	printf("Error: pointer cannot be NULL\n"), exit(ERR_PTR);
      
      for(int j = 0; j < n; j++)
	{
	  a[i][j] = rand_double();
	  b[i][j] = rand_double();
	  c[i][j] = rand_double();
	}
    }
}

//Print matrix on standard output
void print_matrix(const int n, const double **m)
{
  if (!m)
    printf("Error: pointer cannot be NULL\n"), exit(ERR_PTR);
  
  printf("n = %d\n", n);
  
  for (int i = 0; i < n; i++)
    {
      if (!m[i])
	printf("Error: pointer cannot be NULL\n"), exit(ERR_PTR);
      
      for (int j = 0; j < n; j++)
	{
	  printf("%lf ", m[i][j]);
	}
      printf("\n");
    }
}

//Alloc memory
double **alloc_matrix(int n)
{
  double **m = aligned_alloc(ALIGN, sizeof(double) * n);

  if (!m)
    return printf("Error: cannot allocate memory\n"), NULL;
  
  for (int i = 0; i < n; i++)
    {
      m[i] = aligned_alloc(ALIGN, sizeof(double) * n);
      if (!m[i])
	return printf("Error: cannot allocate memory\n"), NULL;
    }
  
  return m;
}

//Free memory
void free_matrix(int n, double **m)
{
  if (!m)
    printf("Error: pointer cannot be NULL\n"), exit(ERR_PTR);
  
  for (int i = 0; i < n; i++)
    {
      free(m[i]);
      if (!m[i])
	printf("Error: pointer cannot be NULL\n"), exit(ERR_PTR);
    }
  
  free(m);
}

//Main function
int main(int argc, char **argv)
{
  //Check argument
  if (argc != 2)
    return printf("Usage: ./%s [size]\n", argv[0]), ERR_ARG;
  
  int n = atoi(argv[1]);
  if (n <= 0)
    return printf("You must use a positive number\n"), ERR_ARG;
  if (n > MAX_N)
    return printf("You must enter a number <= %d\n", MAX_N);
  
  //Alloction
  double **a = alloc_matrix(n);
  if (!a)
    return ERR_PTR;
  double **b = alloc_matrix(n);
  if (!b)
    return ERR_PTR;
  double **c = alloc_matrix(n);
  if (!c)
    return ERR_PTR;
  
  //Initialisation
  init_seed();
  init_matrix(n, a, b, c);
  
  //Compute
  for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
	{
	  for (int k = 0; k < n; k++)
	    {
	      c[i][j] += a[j][k] * b[k][j];
	    }
	}
    }

  //Print
  print_matrix(n, c);

  //Free memory
  free_matrix(n, a);
  free_matrix(n, b);
  free_matrix(n, c);
  
  return 0;
}
