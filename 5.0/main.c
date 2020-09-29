#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

//Free memory
void free_matrix(int n, double **a, double **b, double **c)
{
  for(int i = 0; i < n; i++)
    {
      free(a[i]);
      free(b[i]);
      free(c[i]);
    }
  free(a);
  free(b);
  free(c);

}

//Main function
int main(int argc, char **argv)
{
  //Check argument
  if(argc != 2)
    return 1;
  
  int n = atoi(argv[1]);

  //Alloction
  double **a = malloc(sizeof(double *) * n);
  double **b = malloc(sizeof(double *) * n);
  double **c = malloc(sizeof(double *) * n);

  for(int i = 0; i < n; i++)
    {
      a[i] = malloc(sizeof(double) * n);
      b[i] = malloc(sizeof(double) * n);
      c[i] = malloc(sizeof(double) * n);
    }

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
  free_matrix(n, a, b, c);
  
  return 0;
}
