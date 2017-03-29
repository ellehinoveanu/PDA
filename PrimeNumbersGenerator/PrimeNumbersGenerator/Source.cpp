#include<iostream>
#include<cstdlib>
#include<math.h>
#include"mpi.h"

#define M 2000
#define SIZE 15

bool verifyIfPrime(int number)
{
	if (number < 3 && number != 2) return false;
	for (int index = 3; index <= sqrt(number); index++)
	{
		if (number% index == 0) return false;
	}
	return true;
}

int main(int argc, char *argv[])
{
	int numberOfProcesses, processId, start, step;
	numberOfProcesses = SIZE;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &processId);
	MPI_Comm_size(MPI_COMM_WORLD, &numberOfProcesses);

	start = (processId * 2) + 1;
	step = numberOfProcesses * 2;
	for (int index = start; index <= M; index += step) {
		if (verifyIfPrime(index)) {
			printf("%d\n", index);
		}
	}
	MPI_Finalize();
}