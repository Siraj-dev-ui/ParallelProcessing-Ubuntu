/* 
** DESCRIPTION: Multiply a vector with a scalar
** COMPILE:     mpic++ -o vecmult vecmult.cpp
** RUN:         mpiexec -n 2 -machinefile machines $PWD/vecmult
**
*/

#include <iostream>
#include <stdlib.h>
#include <mpi.h>

using namespace std;

#define NPROCS  4          // Number of processes
#define N       10000
#define LOCAL_N (N/NPROCS)

int main (int argc, char **argv)
{
	int i;
	int myrank, nprocs;
	int namelen;
	char name[MPI_MAX_PROCESSOR_NAME];

	double a[N], factor, local_a[LOCAL_N];


	/* Initialize MPI and set command line arguments */ 
	MPI_Init(&argc, &argv);

	/* Determine the number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

	/* Determine own rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	/* Determine the node name */
	MPI_Get_processor_name(name, &namelen);

	/* flush results in the output being sent immediately without buffering */
	cout << "Process " << myrank << "/" << nprocs << "started on " << name << "\n" << flush;

	if (LOCAL_N * nprocs != N) {
		if (myrank == 0) {
			cerr << "Illegal number of processes (need " << NPROCS << ")\n";
		}
		MPI_Finalize();
		exit(1);
	}


	if (myrank == 0) {
		/* Initialize a and factor. (typically: read from a file) */
		for (i=0; i<N; i++) {
			a[i] = i/10.0;
		}
		factor = 10.0;
	}

	/* Process 0 sends factor to all processes */
	MPI_Bcast(&factor, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	/* Process 0 distributes a to all processes */
	MPI_Scatter(a, LOCAL_N, MPI_DOUBLE, local_a, LOCAL_N,
				MPI_DOUBLE, 0, MPI_COMM_WORLD);

	/* Multiply the local part of a with factor */
	for (i=0; i<LOCAL_N; i++)
		local_a[i] *= factor;

	/* Collect the local results in process 0 */
	MPI_Gather(local_a, LOCAL_N, MPI_DOUBLE, a, LOCAL_N, 
			   MPI_DOUBLE, 0, MPI_COMM_WORLD);

	/*
	** Note: of course, this program is not efficient, since there is not enough
	** computation. However, imagine that instead of the simple multiplication
	** a complex function must be caclulated, which depends on a[i] und factor.
	*/

	if (myrank == 0) {
		/* Output of a. (typically: write into file) */
		for (i=0; i<N; i+=N/20) {
			cout << "a[" << i << "] = " << a[i] << "\n";
		}
	}

	/* Shut down MPI */
	MPI_Finalize();

	return 0;
}

