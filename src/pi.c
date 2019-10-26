#include <stdio.h>
#include <mpi.h>
#define INTERVALS 1000000

int main(int argc, char* argv[])
{
  MPI_Init (&argc, &argv);

  int process_rank, num_processes;
  MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
  MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
  MPI_Barrier(MPI_COMM_WORLD);

  double elapsed_time = -MPI_Wtime();

	double area;	/* The final anser */
	double ysum;	/* Sum of rectangle heights */
	double xi;	/* Midpoint of interval */
	int i;	

	ysum = 0.0;

	for (i=0; i < INTERVALS; i++)
	{
		xi=((1.0/INTERVALS)*(i+0.5));
		ysum+=4.0/(1.0+xi*xi);
	}

  elapsed_time += MPI_Wtime();

  MPI_Finalize();

  if (process_rank == 0) {
  	area = ysum * (1.0/INTERVALS);
  	printf("pi is %13.11f\n", area);
    printf("Calculated in %f\n", elapsed_time);
    fflush (stdout);
  }
  
  return 0;
}
