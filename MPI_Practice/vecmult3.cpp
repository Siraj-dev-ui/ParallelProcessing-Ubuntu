/* 
** DESCRIPTION: Multiply a vector with a scalar
** COMPILE:     mpic++ -o vecmult3 vecmult3.cpp
** RUN:         mpiexec -n 2 -machinefile machines $PWD/vecmult3
**
** This version works with arbitrary vector lengths by using Scatterv/Gatherv.
*/

#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <mpi.h>

using namespace std;

int main (int argc, char **argv)
{
	int i;
	int myrank, nprocs;
	int namelen;
	char name[MPI_MAX_PROCESSOR_NAME];

	double *a = NULL, factor;
	int *sizes = NULL;
	int *displs = NULL;

	int n;
	double *local_a;
	int local_n;


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

	
	/* Check number of arguments */
	if (argc < 2) {
		if (myrank == 0) {
			cerr << "Usage: mpiexec -n <np> ... vecmult3 <array-len>\n"
				 << "       <array-len>: Length of the array\n";
		}
		MPI_Finalize();
		exit(1);
	}

	/* Warning: we should check the argument here! (i.e. whether it is a number) */
	n = atoi(argv[1]);


	if (myrank == 0) {
		/* Allocate the vector. */
		a = new double[n];

		/* Initialize a and factor. (typically: read from a file) */
		for (i=0; i<n; i++) {
			a[i] = i/10.0;
		}
		factor = 10.0;

		/* Allocate and initialize the parameters for Scatterv / Gatherv */
		sizes = new int[nprocs];
		displs = new int[nprocs];

		for (i=0; i<nprocs; i++) {
			/*
			** Equal distribution of n elements to nprocs processes.
			** sizes[i] is the number of elements for process i,
			** displs[i] is the index of the first Element for process i.
			** The same formula can also be used by each process to determine
			** which part of the global data it possesses.
			*/
			sizes[i] = (n + i) / nprocs;
			displs[i] = n / nprocs * i;
			if (i > nprocs - n % nprocs)
				displs[i] += i - (nprocs - n % nprocs);

			cout << "Process " << i << ": displ = " << displs[i] << ", size = " << sizes[i] << "\n";

			/* Assert that the distribution is correct. */
			assert((i==0) || (displs[i] == displs[i-1] + sizes[i-1]));
		}
		assert(displs[i-1] + sizes[i-1] == n);
	}

	
	/* Determine the size of the local part of the array and allocate it */
	local_n = (n + myrank) / nprocs;
	local_a = new double[local_n];

	cout << "Process " << myrank << ": local_n = " << local_n << "\n" << flush;
	fflush(stdout);


	/* Process 0 sends factor to all processes */
	MPI_Bcast(&factor, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	/* Process 0 distributes a to all processes */
	MPI_Scatterv(a, sizes, displs, MPI_DOUBLE, local_a, local_n,
				 MPI_DOUBLE, 0, MPI_COMM_WORLD);

	/* Multiply the local part of a with factor */
	for (i=0; i<local_n; i++)
		local_a[i] *= factor;

	/* Collect the local results in process 0 */
	MPI_Gatherv(local_a, local_n, MPI_DOUBLE, a, sizes, displs,
				MPI_DOUBLE, 0, MPI_COMM_WORLD);

	/*
	** Note: of course, this program is not efficient, since there is not enough
	** computation. However, imagine that instead of the simple multiplication
	** a complex function must be caclulated, which depends on a[i] und factor.
	*/

	if (myrank == 0) {
		/* Output of a. (typically: write into file) */
		for (i=0; i<n; i+=n/20) {
			cout << "a[" << i << "] = " << a[i] << "\n";
		}
	}

	/* Shut down MPI */
	MPI_Finalize();

	return 0;
}

