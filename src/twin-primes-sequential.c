#include <math.h>
#include <stdio.h>

#undef show_primes

int is_prime(long n) {
  /* Implements a primality test on n

  The algorithm used is to simply test primes for factors using trial 
  division from 2 to sqrt(n).

  There are better algorithms for this, but this is simple to understand
  and implement.
  */

  for (long test = 2; test <= sqrtl(n); test++) {
    if (n % test == 0) {
      return 0;
    }
  }

  return 1;
}

int main() {
  int last_was_prime = 0;
  int last_was_twin = 0;
  int count = 0;
  int prime_count = 0;

  for (int i = 1; i < 1000000; i+=2) {
    if (is_prime(i)) {
      prime_count++;
      if (last_was_prime) {
        count += 1;
        if (!last_was_twin) {
          count += 1;
        }
        #ifdef show_primes
          printf("%d and %d (count is %d)\n", i-2, i, count);
        #endif
        last_was_twin = 1;
      } else {
        last_was_twin = 0;
      }
      last_was_prime = 1;
    } else {
      last_was_prime = 0;
      last_was_twin = 0;
    }
  }

  printf("Found %d primes and %d twin primes\n", prime_count, count);

  return 0;
}
