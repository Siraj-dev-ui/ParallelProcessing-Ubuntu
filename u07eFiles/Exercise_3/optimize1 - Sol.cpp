int main(int argc, char *argv[])
{
	int myrank, nprocs;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	if (nprocs != 4) {
		if (myrank == 0)
			std::cerr << "Error: need exactly 4 processes" << std::endl;
		MPI_Finalize();
		exit(1);
	}

	initialize();

	// Start timing (only rank 0 will measure full timing)
	auto start = std::chrono::high_resolution_clock::now();

	// Each process computes only one configuration
	double localCost;
	switch (myrank) {
		case 0: localCost = computeCostForConfigOne(); break;
		case 1: localCost = computeCostForConfigTwo(); break;
		case 2: localCost = computeCostForConfigThree(); break;
		case 3: localCost = computeCostForConfigFour(); break;
	}

	// Reduce to find the minimum cost across all processes
	double minCost;
	MPI_Reduce(&localCost, &minCost, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);

	// Only root prints results
	if (myrank == 0) {
		auto end = std::chrono::high_resolution_clock::now();
		std::cout << "Time: " << (end - start)/std::chrono::milliseconds(1) << "ms" << std::endl;
		std::cout << "Minimum cost: " << minCost << std::endl;
		std::cout << "[The correct minimum cost is: 32.8638]" << std::endl;
	}

	MPI_Finalize();
	return 0;
}
