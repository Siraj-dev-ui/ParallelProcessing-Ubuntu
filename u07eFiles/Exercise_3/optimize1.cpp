/************************************************************************
 *  Simple optimization task: evaluate four configurations and compute  *
 *  the minimum of the results.                                         *
 ************************************************************************/

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <chrono>
#include <mpi.h>

/*
 * Initialization and the four functions computing the cost for different
 * configurations.
 */
extern void initialize();
extern double computeCostForConfigOne();
extern double computeCostForConfigTwo();
extern double computeCostForConfigThree();
extern double computeCostForConfigFour();

/*
 * Auxiliary function for computing the minimum of four values.
 */
double min(double v1, double v2, double v3, double v4)
{
	if (v2 < v1)
		v1 = v2;
	if (v4 < v3)
		v3 = v4;
	return v1<v3 ? v1 : v3;
}

int main(int argc, char *argv[])
{
	int myrank, nprocs;
	
	/* Initialize MPI and set arguments */
	MPI_Init(&argc, &argv);
	
	/* Determine the number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	
	/* Determine own rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	
	if (nprocs != 4) {
		if (myrank == 0)
			std::cerr << "Error: need exactly 4 processes" << std::endl;
		MPI_Finalize();
		exit(1);
	}

	initialize();

	/* Start time */
	auto start = std::chrono::high_resolution_clock::now();
	
	/* Compute the cost of each configuration. */
	double c0 = computeCostForConfigOne();
	double c1 = computeCostForConfigTwo();
	double c2 = computeCostForConfigThree();
	double c3 = computeCostForConfigFour();
	
	/* Compute the minimum of the four values. */
	double minCost = min(c0, c1, c2, c3);

	/* Print the time needed */
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "Time: " << (end - start)/std::chrono::milliseconds(1) << "ms" << std::endl;

	/* Print the result. */
	std::cout << "Mininum cost: " << minCost << std::endl;
	std::cout << "[The correct mininum cost is: 32.8638]" << std::endl;
	
	MPI_Finalize();
	return 0;
}

