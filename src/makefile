all: pi twin-primes-sequential twin-primes-mpi prime-gap

twin-primes-sequential: twin-primes-sequential.c
	gcc $< -o $@ -lm 
	./$@

twin-primes-mpi: twin-primes-mpi.c
	mpicc -O -o $@ $< -lm
	mpirun -n 4 ./twin-primes-mpi 1000000

prime-gap: prime-gap.c
	mpicc -O -o $@ $< -lm
	mpirun -n 4 ./prime-gap 1000000

pi: pi.c
	gcc $< -o $@ -lm 
	./$@	

clean:
	rm -f twin-primes-sequential twin-primes-mpi prime-gap