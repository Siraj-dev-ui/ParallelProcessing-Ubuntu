/**************************************************
 *                                                *
 *  DO NOT EDIT / MODIFY ANY CODE IN THIS FILE!!  *
 *                                                *
 **************************************************/

#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <chrono>

/* Runtime of the functions in milliseconds. */
static const int runtime = 500;

/* How often to repeat the computation for the desired runtime. */
static int repeat;

/* Perform a small benchmark to determine the value of 'repeat'. */
void initialize() 
{
	repeat = 0;
	volatile static double trash;
	double res = 0;
	std::chrono::duration<float> duration = std::chrono::milliseconds(runtime);
	auto start = std::chrono::high_resolution_clock::now();
	while (std::chrono::high_resolution_clock::now() - start < duration) {
		for (int i=0; i<100000; i++)
			res += sin((i+1000*repeat)/100.0);
		repeat++;
	}
	trash = res;
}

/* Runs for 'runtime' milliseconds and returns a more or less random result. */
double computeCost(int configuration) 
{
	double res;
	int rep = repeat * (1 + 0.9*sin(configuration*3.1416/50));
	for (int n=0; n<rep; n++) {
		res = 0;
		for (int i=0; i<100000; i++)
			res += sin((i+1000*configuration)/100.0);
	}
	return fabs(res);
}

double computeCostForConfigOne()
{
	return computeCost(1);
}

double computeCostForConfigTwo()
{
	return computeCost(2);
}

double computeCostForConfigThree()
{
	return computeCost(3);
}

double computeCostForConfigFour()
{
	return computeCost(4);
}
