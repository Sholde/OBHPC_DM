#ifndef _rand_h_
#define _rand_h_

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

#endif //!_rand_h_
