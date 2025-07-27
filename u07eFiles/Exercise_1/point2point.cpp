/***************************************************************************
 * Point to point communication
 *
 * Run this program with 4 processes!!
 *
 ***************************************************************************/

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <mpi.h>

// int main(int argc, char *argv[])
// {
// 	int myrank, nprocs;
// 	int myval;
// 	MPI_Status status;

// 	/* Initialize MPI and set arguments */
// 	MPI_Init(&argc, &argv);

// 	/* Determine the number of processes */
// 	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

// 	/* Determine own rank */
// 	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

// 	if (nprocs < 4)
// 	{
// 		if (myrank == 0)
// 			std::cerr << "Error: need at least 4 processes" << std::endl;
// 		MPI_Finalize();
// 		exit(1);
// 	}

// 	myval = myrank;
// 	switch (myrank)
// 	{
// 	case 1:
// 		MPI_Send(&myval, 1, MPI_INT, 3, 0, MPI_COMM_WORLD);
// 		break;
// 	case 3:
// 		MPI_Recv(&myval, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
// 		break;
// 	case 2:
// 		MPI_Send(&myval, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
// 		break;
// 	case 0:
// 		MPI_Recv(&myval, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, &status);
// 	}

// 	// ===========================================================
// 	// POINT-TO-POINT COMMUNICATION IMPLEMENTATION
// 	// if (myrank == 1)
// 	// {
// 	// 	MPI_Send(&myval, 1, MPI_INT, 3, 0, MPI_COMM_WORLD);
// 	// }
// 	// else if (myrank == 3)
// 	// {
// 	// 	MPI_Recv(&myval, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
// 	// }
// 	// else if (myrank == 2)
// 	// {
// 	// 	MPI_Send(&myval, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
// 	// }
// 	// else if (myrank == 0)
// 	// {
// 	// 	MPI_Recv(&myval, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, &status);
// 	// }
// 	// ===========================================================

// 	std::cout << "Process " << myrank << ": my value is " << myval << std::endl;

// 	MPI_Finalize();
// 	return 0;
// }

int main(int argc, char **argv)
{
	int myrank;
	int a[8] = {1, 2, 3, 4, 5, 6, 7, 8};
	int b[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Scatter(a, 2, MPI_INT, b, 2, MPI_INT, 0, MPI_COMM_WORLD);
	if (myrank == 1)
		std::cout << b[0] << " " << b[2] << std::endl;
	MPI_Finalize();
	return 0;
}