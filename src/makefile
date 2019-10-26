all: pi twin-primes-sequential twin-primes-mpi prime-gap

twin-primes-sequential: twin-primes-sequential.c
	gcc $< -o $@ -lm 
	./$@

twin-primes-mpi: twin-primes-mpi.c
	mpicc -O -o $@ $< -lm
	mpirun -n 1 ./twin-primes-mpi 1000000
	mpirun -n 2 ./twin-primes-mpi 1000000
	mpirun -n 3 ./twin-primes-mpi 1000000
	mpirun -n 4 ./twin-primes-mpi 1000000

prime-gap: prime-gap.c
	mpicc -O -o $@ $< -lm
	mpirun -n 1 ./prime-gap 1000000
	mpirun -n 2 ./prime-gap 1000000
	mpirun -n 3 ./prime-gap 1000000
	mpirun -n 4 ./prime-gap 1000000

pi: pi.c
	mpicc -O -o $@ $< -lm
	mpirun -n 1 ./pi
	mpirun -n 2 ./pi
	mpirun -n 3 ./pi
	mpirun -n 4 ./pi

clean:
	rm -f pi twin-primes-sequential twin-primes-mpi prime-gap