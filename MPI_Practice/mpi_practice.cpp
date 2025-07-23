/*
** DESCRIPTION: Send a message back and forth
** COMPILE:     mpic++ -O -o pingpong pingpong.cpp
** RUN:         mpiexec -n 2 -machinefile machines $PWD/pingpong <passes> <msg-len>
*/

#include <iostream>
#include <stdlib.h>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv)
{
    int i;
    int passes;
    int size;
    char *buf;
    int myrank, nprocs;
    int namelen;
    char name[MPI_MAX_PROCESSOR_NAME];
    MPI_Status status;
    double start, end;

    /* Initialize MPI and set command line arguments */
    MPI_Init(&argc, &argv);

    /* Determine the number of processes */
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    /* Determine own rank */
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    /* Determine the node name */
    MPI_Get_processor_name(name, &namelen);

    /* flush results in the output being sent immediately without buffering */
    cout << "Process " << myrank << "/" << nprocs << "started on " << name << "\n"
         << flush;

    /* Check number of processes */
    if (nprocs != 2)
    {
        if (myrank == 0)
        {
            cerr << "Need 2 processes, have " << nprocs << "\n";
        }
        MPI_Finalize();
        exit(1);
    }

    /* Check number of arguments */
    if (argc < 3)
    {
        if (myrank == 0)
        {
            cerr << "Usage: mpiexec -n 2 ... pingpong <passes> <msg-len>\n"
                 << "       <passes>:  number of messages to be sent\n"
                 << "       <msg-len>: message size in Bytes\n";
        }
        MPI_Finalize();
        exit(1);
    }

    /* Warning: we should check the arguments here! (i.e. whether they are numbers) */
    passes = atoi(argv[1]);
    size = atoi(argv[2]);
    buf = new char[size];

    /* Initialize the message */
    for (i = 0; i < size; i++)
        buf[i] = i % 256;

    if (myrank == 0)
    {
        /* PROCESS 0 */

        /* Determine the current time */
        start = MPI_Wtime();

        for (i = 0; i < passes; i++)
        {
            /* Send message to process 1, tag = 42 */
            MPI_Send(buf, size, MPI_CHAR, 1, 42, MPI_COMM_WORLD);

            /* Wait for the answer, tag is not relevant */
            MPI_Recv(buf, size, MPI_CHAR, 1, MPI_ANY_TAG, MPI_COMM_WORLD,
                     &status);
        }

        /* Determine the current time */
        end = MPI_Wtime();

        cout << myrank << ": Time for one message: "
             << ((end - start) * 1e6 / (2 * passes)) << "us\n";
        cout << myrank << ": Bandwidth: "
             << (size * 2 * passes / (1024 * 1024 * (end - start))) << "MB/s\n";
    }
    else
    {
        /* PROCESS 1 */

        for (i = 0; i < passes; i++)
        {
            /* Wait for message from process 0, tag is not relevant */
            MPI_Recv(buf, size, MPI_CHAR, 0, MPI_ANY_TAG, MPI_COMM_WORLD,
                     &status);

            /* Send message back to process 0, tag = 24 */
            MPI_Send(buf, size, MPI_CHAR, 0, 24, MPI_COMM_WORLD);
        }
    }

    /* Shut down MPI */
    MPI_Finalize();

    return 0;
}
