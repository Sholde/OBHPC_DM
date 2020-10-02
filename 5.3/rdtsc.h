#ifndef _rdtsc_h_
#define _rdtsc_h_

static inline unsigned long long rdtsc()
{
  unsigned long long a, d;

  __asm__ volatile ("rdtsc" : "=a" (a), "=d" (d));

  return (d << 32) | a;
}

#endif //!_rdtsc_h_
