#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRSIZE 100

void main(int argc, char* argv[]) {
	int rank, size;
	MPI_Status status;
	MPI_Request request;
	int done, myfound, fragmentSize;
	int array[ARRSIZE];
	int *fragment;
	int i, j, dummy, index;
	FILE *file = fopen("file.txt", "r");;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	myfound = 0;
	if (rank == 0) {		
		file = fopen("file.txt", "r");
		for (i = 0; i<ARRSIZE; ++i) {
			fscanf(file, "%d", &array[i]);
		}
	}
	fragmentSize = ARRSIZE / size;
	fragment = (int *)malloc(fragmentSize * sizeof(int));
	MPI_Scatter(array, fragmentSize, MPI_INT, fragment, fragmentSize, MPI_INT, 0, MPI_COMM_WORLD);
	//MPI_Barrier(MPI_COMM_WORLD);
	MPI_Irecv(&dummy, 1, MPI_INT, MPI_ANY_SOURCE, 86, MPI_COMM_WORLD, &request);
	MPI_Test(&request, &done, &status);
	i = 0;
	while (!done && i<fragmentSize) {
		if (fragment[i] == 11) {
			dummy = 123;
			for (j = 0; j < size; ++j) {
				MPI_Send(&dummy, 1, MPI_INT, j, 86, MPI_COMM_WORLD);
			}
			printf("P:%d found it at local index %d\n", rank, i);
			myfound = 1;
		}
		MPI_Test(&request, &done, &status);
		++i;
	}
	if (!myfound) {
		if (i == 0)
			index = 0;
		else
			index = i - 1;
		printf("P:%d stopped at local index %d\n", rank, index);
	}
	MPI_Finalize();
}