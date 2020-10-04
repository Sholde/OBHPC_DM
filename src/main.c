#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "def.h"
#include "rand.h"
#include "rdc.h"

//Main function
int main(int argc, char **argv)
{
  //Check argument (needed 3)
  if (argc != 3)
    return printf("Usage: %s [size] [output file]\n", argv[0]), ERR_ARG;
  
  int n = atoi(argv[1]);

  //Check number (needed to be positive)
  if (n <= 0)
    return printf("You must use a positive number\n"), ERR_ARG;
  if (n > MAX_N)
    return printf("You must enter a number <= %d\n", MAX_N);

  //Alloction
  rdc_t m = rdc_t_alloc(n);
  if (!m)
    return printf("Error: pointer cannot be NULL\n"), ERR_PTR;
  
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
