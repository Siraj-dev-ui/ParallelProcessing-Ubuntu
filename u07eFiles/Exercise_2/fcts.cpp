/***************************************************************************
 * Auxiliary functions for parallel implementation of the 'map' operation. *
 *                                                                         *
 * DO NOT MODIFY ANY CODE IN THIS FILE!                                    *
 *                                                                         *
 ***************************************************************************/

#include <stdlib.h>
#include <math.h>

#define N 10000

void read_data(double *x)
{
	for (int i=0; i<N; i++)
		x[i] = sin(3*i); 
}

double complex_fct(double x)
{
	return cos(x*sin(x-1));
}

bool check_data(double *y)
{
	for (int i=0; i<N; i++) {
		if (y[i] != complex_fct(sin(3*i)))
			return false;
	}
	return true;
}



