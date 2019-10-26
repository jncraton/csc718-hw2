#include <stdio.h>
#include <mpi.h>
#define INTERVALS 100000000

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

	int process_intervals = INTERVALS / num_processes;
	int process_start = process_rank * process_intervals;
	int process_end = (process_rank + 1) * process_intervals;

	for (i=process_start; i < process_end; i++)
	{
		xi=((1.0/INTERVALS)*(i+0.5));
		ysum+=4.0/(1.0+xi*xi);
	}

	double global_sum;

  MPI_Reduce(&ysum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
           
  elapsed_time += MPI_Wtime();

  MPI_Finalize();

  if (process_rank == 0) {
  	area = global_sum * (1.0/INTERVALS);
  	printf("Calculated pi as %13.11f in %f\n", area, elapsed_time);
    fflush (stdout);
  }
  
  return 0;
}
