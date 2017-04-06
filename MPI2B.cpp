#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#define SIZE 100
#define SEARCHEDVALUE 32


int main(int argc, char *argv[])
{
	int processId, nrOfProcesses, portionSize, index, portionFound[SIZE], totalFoundArray[SIZE + 10], poz;
	int array[SIZE], portionArray[SIZE];
	bool hasBeenFound = false;

	srand(time(NULL));

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &processId);
	MPI_Comm_size(MPI_COMM_WORLD, &nrOfProcesses);

	portionSize = SIZE / nrOfProcesses;
	if (SIZE % nrOfProcesses != 0) {
		portionSize = portionSize +1;
	}

	MPI_Barrier(MPI_COMM_WORLD);

	if (processId == 0) {
		for (int i = 0; i < SIZE; i++) {
			array[i] = rand() % 100;
			printf("%d, ", array[i]);
			totalFoundArray[i] = -1;
		}
	}

	MPI_Scatter(array, portionSize, MPI_INT, portionArray, portionSize, MPI_INT, 0, MPI_COMM_WORLD);

	for (int i = 0; i < portionSize; i++)
		portionFound[i] = 0;

	index = 0;
	for (int i = 0; i < portionSize; i++) {
		if (portionArray[i] == SEARCHEDVALUE) {
			portionFound[index++] = i + processId * portionSize;
		}
	}

	MPI_Gather(portionFound, portionSize, MPI_INT, totalFoundArray, portionSize, MPI_INT, 0, MPI_COMM_WORLD);

	if (processId == 0) {
		for (int i = 0; i < SIZE + 10; i++)
			if (totalFoundArray[i] > 0)
				hasBeenFound = true;
		if (hasBeenFound) {
			printf("\n\The found positions are: ");
			for (int i = 0; i < SIZE + 10; i++)
				if (totalFoundArray[i] != 0)
					printf("%d ", totalFoundArray[i]);
		}
		else
		{
			printf("The element has not been found.");
		}


	}


	MPI_Finalize();
	return 0;
}