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

int main(int argc, char *argv[])
{
    int myrank, nprocs;
    MPI_Status status;

    /* Initialize MPI and set arguments */
    MPI_Init(&argc, &argv);

    /* Determine the number of processes */
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    /* Determine own rank */
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    double x[10000], xl[1250];
    double y[10000], yl[1250];
    int myrank;
    // int n = 10000 / nprocs;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    if (myrank == 0)
    {
        … // initialization of x[]
    }
    // Insert your parallel code for computing y[] here

    MPI_Scatter(x, 1250, MPI_DOUBLE, xl, 1250, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Gather(yl, 1250, MPI_DOUBLE, y, 1250, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (myrank == 0)
    {
        … // continue processing using y[]
    }
    MPI_Fnalize();
    return 0;
}