#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

/*
 * mpicc -std=c99 broadcast.c -o broadcast
 * mpiexec -np 5 broadcast
 */
int main(int argc, char* argv[])
{
	int procRank,procCount;
	enum { tagSend = 1 };
	
	MPI_Init(&argc,&argv);
	
	MPI_Comm_size(MPI_COMM_WORLD,&procCount);
	MPI_Comm_rank(MPI_COMM_WORLD,&procRank);
	
	printf("Start[%d]/[%d] \n",procRank,procCount);
	
	int message = -1;

	if(procRank == 0)
	{
		message = 42;
	}

	// This line, broadcasts the message to all other processes, if removed, they become -1
	MPI_Bcast(&message, 1, MPI_INT, 0, MPI_COMM_WORLD);
	printf("proc %d recv. bcast %d \n", procRank, message);

	MPI_Finalize();

	return EXIT_SUCCESS;
}
