#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
/*
* mpicc -std=c99 hello.c -o hello
* mpiexec -np 3 ./hello
*/
int main(int argc, char* argv[])
{
	int procRank, procCount;
	
	MPI_Init(&argc, &argv);
	
	MPI_Comm_size(MPI_COMM_WORLD, &procCount);
	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
	
	printf("Start[%d]/[%d]: Hello World\n",procRank,procCount);
	
	MPI_Finalize();
	return EXIT_SUCCESS;
}
