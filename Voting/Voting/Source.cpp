#include<cstdio>
#include<cstdlib>
#include<ctime>
#include"mpi.h"

#define NRPROCESSES 9


int main(int argc, char** argv) {
	MPI_Init(NULL, NULL);

	int processRank;
	MPI_Comm_rank(MPI_COMM_WORLD, &processRank);
	int processSize = NRPROCESSES;
	MPI_Comm_size(MPI_COMM_WORLD, &processSize);

	
	srand(time(NULL));
	int secretNumber = rand()%100 +1;
	int receivedNumber = 0;
	
	printf("My number is %d and I am process nr. %d \n", secretNumber,processRank);

	if (processRank != 0) {
		MPI_Recv(&receivedNumber, 1, MPI_INT, processRank - 1, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("Process %d received number %d from process %d\n", processRank, receivedNumber,
			processRank - 1);
	}
	if (receivedNumber > secretNumber) {
		MPI_Send(&receivedNumber, 1, MPI_INT, (processRank + 1)%processSize, 0,MPI_COMM_WORLD);
	}
	else MPI_Send(&secretNumber, 1, MPI_INT, (processRank + 1)% processSize, 0,MPI_COMM_WORLD);

	if (processRank == 0) {
		MPI_Recv(&receivedNumber, 1, MPI_INT, processSize - 1, 0, MPI_COMM_WORLD,
			MPI_STATUS_IGNORE);
		printf("Process %d received number %d from process %d\n", processRank, receivedNumber,
			processSize - 1);
	}
	MPI_Finalize();
}