#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mpi.h"

/*
 * mpicc -std=c99 non-blocking.c -o non-blocking
 * mpiexec -np 2 non-blocking
 */
int main(int argc, char* argv[])
{
	int procRank, procCount;
	enum { tagSend = 1};

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &procCount);
	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);


	int message = 0;

	if(procRank == 0)
	{
		sleep(2);
		message = 12345;
		MPI_Request req;
		MPI_Isend(&message, 1, MPI_INT, 1, tagSend, MPI_COMM_WORLD, &req);
		printf("sent: %i\n", message);

		int stop = 0;
		while(stop != 1)
		{
			MPI_Test(&req, &stop, MPI_STATUS_IGNORE);

			if( stop == 1)
				break;

			printf("send waiting ...\n");
			//sleep(1);
		}
		printf("message sent: %i\n", message);
	}

	else if(procRank == 1)
	{
		MPI_Request req;
		MPI_Irecv(&message, 1, MPI_INT, 0, tagSend, MPI_COMM_WORLD, &req);

		int flag = 0;
		while(1)
		{
			MPI_Test(&req, &flag, MPI_STATUS_IGNORE);

			if(flag == 1)
				break;

			printf("recv waiting ...\n");
			sleep(1);
		}
		printf("mesage received: %i\n", message);
	}

	MPI_Finalize();

	return 0;
}
