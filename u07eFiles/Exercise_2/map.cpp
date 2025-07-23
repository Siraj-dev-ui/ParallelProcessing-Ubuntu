/***************************************************************************
 * Parallel implementation of the 'map' operation.
 *
 * Run this program with 1, 2, 4, 8, or 16 processes!!
 * 
 ***************************************************************************/

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <mpi.h>

// Size of arrays. Do not change!
// Note that 10000 can be divided by 1, 2, 4, 8, and 16.
#define N 10000

extern void read_data(double *x);
extern double complex_fct(double x);
extern bool check_data(double *y);

int main(int argc, char* argv[])
{
	int myrank, nprocs;
	MPI_Status status;

	/* Initialize MPI and set arguments */
	MPI_Init(&argc, &argv);

	/* Determine the number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

	/* Determine own rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	if ((nprocs != 1) && (nprocs != 2) && (nprocs != 4) && (nprocs != 8) && (nprocs != 16)) {
		if (myrank == 0)
			std::cerr << "ERROR: need 1, 2, 4, 8, or 16 processes" << std::endl;
		MPI_Finalize();
		exit(1);
	}

	// Input and output array
	double *x;
	double *y;

	// Only process 0 reads the array data into x!
	if (myrank == 0) {
		x = new double[N];
		y = new double[N];
		
		// Read the data into x
		read_data(x);
	}

	// ===========================================================
	
	// Parallelise this loop using all processes!
	// Don't forget that you need to allocate the local arrays for
	// x and y in all the MPI processes
	
	for (int i=0; i<N; i++)
		y[i] = complex_fct(x[i]);
	
	// ===========================================================
	
	// Only process 0 checks and prints the result!
	if (myrank == 0) {
		if (check_data(y))
			std::cout << "Result is correct\n";
		else
			std::cout << "Result is NOT correct\n";
	}
	
	MPI_Finalize();
	return 0;
}



