/***********************************************************************
 *  Simple optimization task: evaluate 100 configurations and compute  *
 *  the minimum of the results.                                        *
 ***********************************************************************/

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <chrono>
#include <mpi.h>

/*
 * Initialization and the function computing the cost for a given
 * configuration.
 */
extern void initialize();
extern double computeCost(int config);


int main(int argc, char *argv[])
{
	int myrank, nprocs;
	
	/* Initialize MPI and set arguments */
	MPI_Init(&argc, &argv);
	
	/* Determine the number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	
	/* Determine own rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	initialize();
	
	/* Start time */
	auto start = std::chrono::high_resolution_clock::now();

	/* Initialize the minimum cost with +infinity. */
	double minCost = std::numeric_limits<double>::infinity();

	/* Compute the minimum cost. */
	for (int i=0; i<100; i++) {
		double c = computeCost(i);
		if (c < minCost)
			minCost = c;
	}
	/* Print the time needed */
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "Time: " << (end - start)/std::chrono::milliseconds(1) << "ms" << std::endl;

	/* Print the result. */
	std::cout << "Mininum cost: " << minCost << std::endl;
	std::cout << "[The correct mininum cost is: 0.456491]" << std::endl;
	
	MPI_Finalize();
	return 0;
}

