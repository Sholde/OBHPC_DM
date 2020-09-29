#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ALIGN 64

//Init random seed
void init_seed()
{
  srand(time(NULL));
}

//Random sign function
char rand_sign(char x, char y)
{
  return (((rand() % (y - x + 1)) + x) ? 1 : -1);
}

//Random int function
double rand_double()
{
  return (double)(rand() % RAND_MAX) / (double)(rand() % RAND_MAX) * rand_sign(0, 1);
}

//Init matrix with random value
void init_matrix(int n, double **a, double **b, double **c)
{
  for(int i = 0; i < n; i++)
    {
      for(int j = 0; j < n; j++)
	{
	  a[i][j] = rand_double();
	  b[i][j] = rand_double();
	  c[i][j] = rand_double();
	}
    }
}

//Print matrix on standard output
void print_matrix(int n, double **m)
{
  printf("n = %d\n", n);
  for(int i = 0; i < n; i++)
    {
      for(int j = 0; j < n; j++)
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

  for(int i = 0; i < n; i++)
    {
      m[i] = aligned_alloc(ALIGN, sizeof(double) * n);
    }
  
  return m;
}

//Free memory
void free_matrix(int n, double **m)
{
  for(int i = 0; i < n; i++)
    {
      free(m[i]);
    }
  free(m);
}

//Main function
int main(int argc, char **argv)
{
  //Check argument
  if (argc != 2)
    return printf("Usage: ./%s [size]\n", argv[0]), 1;
  
  int n = atoi(argv[1]);
  if (n <= 0)
    return printf("You must use a positive number\n"), 1;

  //Alloction
  double **a = alloc_matrix(n);
  double **b = alloc_matrix(n);
  double **c = alloc_matrix(n);
  
  //Initialisation
  init_seed();
  init_matrix(n, a, b, c);
  
  //Compute
  for(int i = 0; i < n; i++)
    {
      for(int j = 0; j < n; j++)
	{
	  for(int k = 0; k < n; k++)
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
