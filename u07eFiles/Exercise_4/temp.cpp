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

void MPIReduce(int argc, char *argv[])
{

    int rank, size;
    int value, result;

    MPI_Init(&argc, &argv);               // Initialize the MPI environment
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get the rank of the process
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the total number of processes

    value = rank + 1; // Each process sets a value (e.g., rank+1)

    // Perform the reduction operation (sum)
    MPI_Reduce(&value, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Print the result on the root process
    if (rank == 1)
    {
        printf("Sum of values from all processes: %d\n", result);
    }

    MPI_Finalize(); // Finalize the MPI environment
}

int main(int argc, char *argv[])
{

    MPIReduce(argc, argv);
    // int myrank, nprocs;
    // MPI_Status status;

    // /* Initialize MPI and set arguments */
    // MPI_Init(&argc, &argv);

    // /* Determine the number of processes */
    // MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    // /* Determine own rank */
    // MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    // double x[10000], xl[1250];
    // double y[10000], yl[1250];
    // int myrank;
    // // int n = 10000 / nprocs;
    // MPI_Init(&argc, &argv);
    // MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    // if (myrank == 0)
    // {
    //     … // initialization of x[]
    // }
    // // Insert your parallel code for computing y[] here

    // MPI_Scatter(x, 1250, MPI_DOUBLE, xl, 1250, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    // MPI_Gather(yl, 1250, MPI_DOUBLE, y, 1250, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // if (myrank == 0)
    // {
    //     … // continue processing using y[]
    // }
    // MPI_Fnalize();
    return 0;
}