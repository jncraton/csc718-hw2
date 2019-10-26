all: pi twin-primes-sequential twin-primes-mpi prime-gap

twin-primes-sequential: twin-primes-sequential.c
	gcc -std=c99 $< -o $@ -lm 
	./$@

twin-primes-mpi: twin-primes-mpi.c
	mpicc -std=c99 -O -o $@ $< -lm
	mpirun -n 1 ./twin-primes-mpi 1000000
	mpirun -n 2 ./twin-primes-mpi 1000000
	mpirun -n 3 ./twin-primes-mpi 1000000
	mpirun -n 4 ./twin-primes-mpi 1000000

prime-gap: prime-gap.c
	mpicc -std=c99 -O -o $@ $< -lm
	mpirun -n 1 ./prime-gap 1000000
	mpirun -n 2 ./prime-gap 1000000
	mpirun -n 3 ./prime-gap 1000000
	mpirun -n 4 ./prime-gap 1000000

pi: pi.c
	mpicc -std=c99 -O -o $@ $< -lm
	mpirun -n 1 ./pi
	mpirun -n 2 ./pi
	mpirun -n 3 ./pi
	mpirun -n 4 ./pi

%-run-rushmore: %
	scp $< washington:~
	scp $< jefferson:~
	scp $< lincoln:~
	scp $< roosevelt:~
	mpirun -n 1 -host washington,jefferson,lincoln,roosevelt ~/$< 10000000
	mpirun -n 2 -host washington,jefferson,lincoln,roosevelt ~/$< 10000000
	mpirun -n 3 -host washington,jefferson,lincoln,roosevelt ~/$< 10000000
	mpirun -n 4 -host washington,jefferson,lincoln,roosevelt ~/$< 10000000

clean:
	rm -f pi twin-primes-sequential twin-primes-mpi prime-gap
