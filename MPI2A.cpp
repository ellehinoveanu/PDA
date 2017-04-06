#include<cstdlib>
#include<ctime>
#include<cstdio>
#include"mpi.h"
#define SIZE 100
#define SEARCHEDNUMBER 15
#define NRPROCESS 20

int main(int argc, char* argv[]) {
	int array[SIZE], nrProcesses, processId, sizeOfPortion, startingPos, endingPos, foundPos, foundFinalPos;
	nrProcesses = NRPROCESS;
	foundPos = -1;
	foundFinalPos = -1;
	srand(time(NULL));

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &processId);
	MPI_Comm_size(MPI_COMM_WORLD, &nrProcesses);

	if (processId == 0)
		for (int index = 0; index < SIZE; index++)
		{
			array[index] = rand() % 100 + 1;
		}

	sizeOfPortion = SIZE / nrProcesses;

	startingPos = processId * sizeOfPortion;
	endingPos = startingPos + sizeOfPortion - 1;

	MPI_Bcast(array, SIZE, MPI_INT, 0, MPI_COMM_WORLD);

	for (int index = startingPos; index < endingPos; index++)
	{
		if (array[index] == SEARCHEDNUMBER)
			foundPos = index;

	}
	MPI_Reduce(&foundPos, &foundFinalPos, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

	if (processId == 0) {
		if (foundFinalPos == -1)
			printf("\nThe number has not been found\n");
		else printf("\nNumber found on position %d", foundFinalPos);
	}


	MPI_Finalize();
	getchar();
}
