#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

/*
 * mpicc -std=c99 ping-pong.c -o pingpong
 * mpiexec -np 2 pingpong
 */
int main(int argc, char* argv[])
{
	int procRank,procCount;
	enum { tagSend = 1 };
	
	MPI_Init(&argc,&argv);
	
	MPI_Comm_size(MPI_COMM_WORLD,&procCount);
	MPI_Comm_rank(MPI_COMM_WORLD,&procRank);
	
	printf("Start[%d]/[%d] \n",procRank,procCount);
	
	int message = 0;

	if(procRank == 0)
	{
		while( message <= 3)
		{
			MPI_Send(&message, 1, MPI_INT, 1, tagSend, MPI_COMM_WORLD);
			printf("Ping:%i\n", message);
			MPI_Recv(&message, 1, MPI_INT, 0, tagSend, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
	}
	else if( procRank == 1)
	{	
		int r = -1;
		while( r <= 3 )
		{
			MPI_Recv(&r, 1, MPI_INT, 0, tagSend, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			r++;
			printf("Pong:%i\n", r);
			MPI_Send(&r, 1, MPI_INT, 1, tagSend, MPI_COMM_WORLD);
		}
	}	

	MPI_Finalize();

	return EXIT_SUCCESS;
}
