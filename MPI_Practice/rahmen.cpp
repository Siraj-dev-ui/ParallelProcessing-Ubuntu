/*
** DESCRIPTION: Template for MPI-Programs
** COMPILE:     mpic++ -o rahmen rahmen.cpp
** RUN:         mpiexec -n 3 -machinefile machines $PWD/rahmen arg1 arg2 ...
*/

#include <iostream>
#include <stdlib.h>
#include <mpi.h>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
	int i;
	int myrank, nprocs;
	int namelen;
	char name[MPI_MAX_PROCESSOR_NAME];
	// std::string name;

	// cout << "-- Arguments: ";
	// for (i = 0; i < argc; i++)
	// 	cout << argv[i] << " ";
	// cout << "\n";

	/* Initialize MPI and set command line arguments */
	MPI_Init(&argc, &argv);

	// std::cout << argc;

	/* Determine the number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

	cout << "MPI_Comm_size : " << nprocs << std::endl;

	/* Determine own rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	cout << "MPI_Comm_rank : " << myrank << std::endl;

	/* Determine the node name */
	MPI_Get_processor_name(name, &namelen);
	cout << "MPI_Get_processor_name : " << nprocs << std::endl;

	/* flush results in the output being sent immediately without buffering */
	// cout << "Process " << myrank << "/" << nprocs << "started on " << name << "\n"
	// << flush;

	// cout << "-- Arguments: ";
	// for (i = 0; i < argc; i++)
	// 	cout << argv[i] << " ";
	// cout << "\n";

	/* Shut down MPI */
	MPI_Finalize();

	return 0;
}
