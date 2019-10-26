all: pi twin-primes-sequential twin-primes-mpi prime-gap

local_size=1200000
remote_size=12000000

twin-primes-sequential: twin-primes-sequential.c
	gcc -std=c99 $< -o $@ -lm 

twin-primes-mpi: twin-primes-mpi.c
	mpicc -std=c99 -O -o $@ $< -lm

prime-gap: prime-gap.c
	mpicc -std=c99 -O -o $@ $< -lm

pi: pi.c
	mpicc -std=c99 -O -o $@ $< -lm

%-run: %
	mpirun -n 1 ./$< $local_size
	mpirun -n 2 ./$< $local_size
	mpirun -n 3 ./$< $local_size
	mpirun -n 4 ./$< $local_size

%-run-rushmore: %
	scp $< washington:~
	scp $< jefferson:~
	scp $< lincoln:~
	scp $< roosevelt:~
	mpirun -n 1 -host washington,jefferson,lincoln,roosevelt ~/$< $(remote_size)
	mpirun -n 2 -host washington,jefferson,lincoln,roosevelt ~/$< $(remote_size)
	mpirun -n 3 -host washington,jefferson,lincoln,roosevelt ~/$< $(remote_size)
	mpirun -n 4 -host washington,jefferson,lincoln,roosevelt ~/$< $(remote_size)

clean:
	rm -f pi twin-primes-sequential twin-primes-mpi prime-gap
