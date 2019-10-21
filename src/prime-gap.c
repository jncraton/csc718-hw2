#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <mpi.h>

#define print_expected_sum
#undef show_process_results

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

int main (int argc, char *argv[]) {
  MPI_Init (&argc, &argv);

  int process_rank, num_processes;
  MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
  MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
  MPI_Barrier(MPI_COMM_WORLD);

  double elapsed_time = -MPI_Wtime();

  long up_to = atol(argv[1]);

  int primes_per_proc = up_to / num_processes / 2;

  if (process_rank == 0) {
    printf("Counting twin primes from 0 to %ld using %d processes and %d primes per process\n",
           up_to, num_processes, primes_per_proc);
    fflush(stdout);
  }

  long * primes;

  if (process_rank == 0) {
    primes = malloc(up_to * sizeof(long));
    for (long i = 1; i <= up_to; i+=2) {
      primes[(i-1) / 2] = i;
    }
  }

  long * local_primes = malloc(sizeof(long) * primes_per_proc);

  MPI_Scatter(primes, primes_per_proc, MPI_LONG,
              local_primes, primes_per_proc, MPI_LONG,
              0, MPI_COMM_WORLD);

  for (long i = 0; i < primes_per_proc; i++) {
    local_primes[i] = is_prime(local_primes[i]);
  }

  MPI_Barrier(MPI_COMM_WORLD);

  MPI_Gather(local_primes, primes_per_proc, MPI_LONG,
             primes, primes_per_proc, MPI_LONG, 
             0, MPI_COMM_WORLD);

  long max_gap = 0;
  int prime_count = 0;
  long last_prime = 0;
  long gap;
  if (process_rank == 0) {
    for (long i = 0; i < up_to / 2; i++) {
    
      prime_count += !!primes[i];

      if (primes[i]) {
        gap = (i*2+1) - last_prime;

        last_prime = (i*2+1);

        if (gap > max_gap) { max_gap = gap; }
      }
    }
  }

  elapsed_time += MPI_Wtime();

  MPI_Finalize();

  if (process_rank == 0) {
    printf("Counted %d primes and a max prime gap of %ld in %f\n", prime_count, max_gap, elapsed_time);
    fflush (stdout);
  }
  
  return 0;
}
