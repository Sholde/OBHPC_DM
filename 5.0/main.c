#include <stdio.h>
#include <stdlib.h>

//Print matrix on standard output
void print_matrix(int n, double **m)
{
  for(int i = 0; i < n; i++)
    {
      printf("| ");
      for(int j = 0; j < n; j++)
	{
	  printf("%lf ", m[i][j]);
	}
      printf("|\n");
    }
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
  for(int i = 0; i < n; i++)
    {
      free(a[i]);
      free(b[i]);
      free(c[i]);
    }
  free(a);
  free(b);
  free(c);
  
  return 0;
}
