#include <stdlib.h>

int main(int argc, char **argv)
{
  if(argc != 2)
    return 1;
  
  int n = atoi(argv[1]);

  double a[n][n], b[n][n], c[n][n];

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
  
  return 0;
}
