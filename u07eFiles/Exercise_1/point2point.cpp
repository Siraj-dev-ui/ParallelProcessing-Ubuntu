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

int main(int argc, char* argv[])
{
	int myrank, nprocs;
	int myval;
	MPI_Status status;

	/* Initialize MPI and set arguments */
	MPI_Init(&argc, &argv);

	/* Determine the number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

	/* Determine own rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	
	if (nprocs < 4) {
		if (myrank == 0)
			std::cerr << "Error: need at least 4 processes" << std::endl;
		MPI_Finalize();
		exit(1);
	}

	myval = myrank;

	// ===========================================================

	// Enter your code here!
	//  - Process 1 should send its value 'myval' to process 3, that receives it in 'myval'
	//  - Process 2 should send its value 'myval' to process 0, that receives it in 'myval'
	// ===========================================================

	std::cout << "Process " << myrank << ": my value is " << myval << std::endl;
    // With 4 Processes, this should print something like:
    //  Process 0: my value is 2
    //  Process 2: my value is 2
    //  Process 1: my value is 1
    //  Process 3: my value is 1
    // I.e., Process 3 should print 1, process 0 should print 2.
	MPI_Finalize();
	return 0;
}



