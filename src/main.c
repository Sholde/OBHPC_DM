#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "def.h"
#include "rand.h"
#include "rdp.h"

//
void print_help(const char *name)
{
  printf("Usage:\n\n");

  printf("Fill the generated matrix with random value:\n\t%s -r [size] [output file]\n", name);

  printf("\n");

  printf("Fill the generated matrix with an positive integer:\n\t%s -n [value] [size] [output file]\n", name);

  printf("\n");

  printf("Compute:\n\t%s -c [size] [input file] [input file] [output file]\n", name);
}

//Main function
int main(int argc, char **argv)
{
  //Check argument (needed 3)
  if (argc < 4)
    {
      print_help(argv[0]);
      return ERR_ARG;
    }
  else if (strcmp(argv[1], "-r") == 0)
    {
      int size = atoi(argv[2]);

      //Check number (needed to be positive)
      if (size <= 0)
	return printf("You must use a positive interger between 1 and 2^31-1\n"), ERR_ARG;

      double *m = matrix_alloc(size);
      if (!m)
	return printf("Error: pointer cannot be NULL\n"), ERR_PTR;
  
      //Initialisation
      matrix_init_random(size, m);
  
      //Print
      matrix_write(argv[3], size, m);

      //Free memory
      matrix_free(size, m);
    }
  else if (strcmp(argv[1], "-n") == 0)
    {
      int n = atoi(argv[2]);
      int size = atoi(argv[3]);
      
      //Check number (needed to be positive)
      if (size <= 0 || size > MAX_N)
	return printf("You must use a positive interger between 1 and %d\n", MAX_N), ERR_ARG;
      
      double *m = matrix_alloc(size);
      if (!m)
	return printf("Error: pointer cannot be NULL\n"), ERR_PTR;
  
      //Initialisation
      matrix_init_integer(size, n, m);
  
      //Print
      matrix_write(argv[4], size, m);

      //Free memory
      matrix_free(size, m);
    }
  else if (strcmp(argv[1], "-c") == 0)
    {
      int size = atoi(argv[2]);

      double *a = matrix_read(argv[3], size);
      if (!a)
	return printf("Error: pointer cannot be NULL\n"), ERR_PTR;
      double *b = matrix_read(argv[4], size);
      if (!b)
	return printf("Error: pointer cannot be NULL\n"), ERR_PTR;
      double *c = matrix_alloc(size);
      if (!c)
	return printf("Error: pointer cannot be NULL\n"), ERR_PTR;

      matrix_compute(size, c, a, b);

      matrix_write(argv[5], size, c);
      
      matrix_free(size, a);
      matrix_free(size, b);
      matrix_free(size, c);
    }
  else
    {
      print_help(argv[0]);
      return ERR_ARG;
    }
  
  return 0;
}
