all: twin-primes-sequential twin-primes-mpi

twin-primes-sequential: twin-primes-sequential.c
	gcc $< -o $@ -lm 
	./$@

twin-primes-mpi: twin-primes-mpi.c
	mpicc -O -o $@ $< -lm
	mpirun -n 4 ./twin-primes-mpi 1000000

clean:
	rm -f twin-primes-sequential twin-primes-mpi