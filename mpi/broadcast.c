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
	
	int message = 1;

	if(procRank == 0)
	{
		MPI_Send(&message, 1, MPI_INT, 1, tagSend, MPI_COMM_WORLD);
		printf("%i -> %i :(%i)\n", procRank, procRank+1, message);
		MPI_Recv(&message, 1, MPI_INT, 1, tagSend, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	else if( procRank == procCount-1 )
	{
		int r = -1;
		MPI_Recv(&r, 1, MPI_INT, procRank-1, tagSend, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		r++;
		printf("%i -> %i :(%i)\n", procRank, 0, r);
		MPI_Send(&r, 1, MPI_INT, 0, tagSend, MPI_COMM_WORLD);
	}
	else
	{	
		int r = -1;
		MPI_Recv(&r, 1, MPI_INT, procRank-1, tagSend, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		r++;
		printf("%i -> %i :(%i)\n", procRank, procRank+1, r);
		MPI_Send(&r, 1, MPI_INT, procRank+1, tagSend, MPI_COMM_WORLD);
	}	

	MPI_Finalize();

	return EXIT_SUCCESS;
}
