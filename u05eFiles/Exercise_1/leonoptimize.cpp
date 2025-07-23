/************************************************************************
 *  Simple optimization task: evaluate four configurations and compute  *
 *  the minimum of the results.                                         *
 ************************************************************************/

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <omp.h>
#include <chrono>

/*
 * Initialization and the four functions computing the cost for different
 * configurations.
 */
extern void initialize();
extern double computeCostForConfigOne();
extern double computeCostForConfigTwo();
extern double computeCostForConfigThree();
extern double computeCostForConfigFour();

/*
 * Auxiliary function for computing the minimum of four values.
 */
double min(double v1, double v2, double v3, double v4)
{
	if (v2 < v1)
		v1 = v2;
	if (v4 < v3)
		v3 = v4;
	return v1<v3 ? v1 : v3;
}


int main(int argc, char *argv[])
{
	initialize();

	/* Start time */
	auto start = std::chrono::high_resolution_clock::now();

	/*
		The resulting speedup: 2135.8/644.4=3.314

		-If the single directive is used one statement will be executed only once by the first arriving thread.
		 After the execution of the threads task it will skip to the next single directive, 
		 if there is one which was not handled before.
		 This means a dynamic distribution of the tasks is achived.
		 Important is that the nowait clause is used.
		-The scheduling of the section directive is implementation defined. 
		 So it could be a static scheduling which leads to bad load balancing, 
		 but in the case of gcc dynamic scheduling is used.
		-The task directive will have good load balancing because a work pool model is used, 
		 but it has more overhead due to the synchronization. The single directive needs to be used to prevent that 
		 multiple threads create new tasks and we end up with more than four tasks.
	*/

	double c0 = 0.0;
	double c1 = 0.0;
	double c2 = 0.0;
	double c3 = 0.0;
	
	/* Compute the cost of each configuration. */
	#pragma omp parallel sections
	{
		#pragma omp section
		c0 = computeCostForConfigOne();
		#pragma omp section
		c1 = computeCostForConfigTwo();
		#pragma omp section
		c2 = computeCostForConfigThree();
		#pragma omp section
		c3 = computeCostForConfigFour();
	}
	
	/* Compute the minimum of the four values. */
	double minCost = min(c0, c1, c2, c3);

	/* Print the time needed */
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "Time: " << (end - start)/std::chrono::milliseconds(1) << "ms" << std::endl;

	/* Print the result. */
	std::cout << "Mininum cost: " << minCost << std::endl;
	std::cout << "[The correct mininum cost is: 32.8638]" << std::endl;

	return 0;
}

