/* 
** DESCRIPTION: Send a message in a circle
**              Correct version using MPI_Isend
** COMPILE:     mpic++ -O -o ring3 ring3.cpp
** RUN:         mpiexec -n 2 -machinefile machines $PWD/ring3 <msg-len>
**
** Execute the program once with message length 100, then with length 1000000!
** What do you notice?
*/

#include <iostream>
#include <stdlib.h>
#include <mpi.h>

using namespace std;

int main (int argc, char **argv)
{
	int size;
	char *sbuf, *rbuf;
	int myrank, nprocs;
	int namelen;
	char name[MPI_MAX_PROCESSOR_NAME];
	MPI_Status status;
	MPI_Request request;

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

	/* Check number of processes */
	if (argc < 2) {
		if (myrank == 0) {
			cerr <<	"Usage: mpiexec -n <np> ... ring3 <msg-len>\n"
				 << "       <msg-len>: message size in Bytes\n";
		}
		MPI_Finalize();
		exit(1);
	}

	/* Warning: we should check the arguments here! (i.e. whether they are numbers) */
	size = atoi(argv[1]);
	sbuf = new char[size];
	rbuf = new char[size];


	/* Set up an MPI send request */
	cout << "Process " << myrank << ": posting send ...\n" << flush;
	MPI_Isend(sbuf, size, MPI_CHAR, (myrank+1) % nprocs, 0,
			  MPI_COMM_WORLD, &request);

	/* Receive the message */
	cout << "Process " << myrank << ": receiving ...\n" << flush;
	MPI_Recv(rbuf, size, MPI_CHAR, (myrank+nprocs-1) % nprocs,
			 0, MPI_COMM_WORLD, &status);

	/* Wait for the message being sent */
	cout << "Process " << myrank << ": waiting for send to complete ...\n" << flush;
	MPI_Wait(&request, &status);

	cout << "Process " << myrank << ": done ...\n" << flush;

	/* Shut down MPI */
	MPI_Finalize();

	return 0;
}

