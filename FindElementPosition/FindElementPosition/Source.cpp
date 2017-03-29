#include "mpi.h"
#include<iostream>
#include<cstdlib>

#define SIZE 6
#define MASTER 0
#define SEARCHEDVALUE 11
#define NUMPROCESSES  7

int main(int argc, char *argv[])
{
	int vector[SIZE] = { 2, 3, 10, 11, 11, 11 },  searchedValue , start, nextStep, counter, processId, numberOfProcesses ;
	searchedValue = SEARCHEDVALUE;
	numberOfProcesses = NUMPROCESSES;
	
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numberOfProcesses);
	MPI_Comm_rank(MPI_COMM_WORLD, &processId);


	start = processId;
	nextStep = numberOfProcesses * 2;
	
	if (processId > SIZE) start = processId%SIZE;

	for (int i = start; i < SIZE; i+= nextStep)
	{
		if (vector[i] == searchedValue)
		{
			printf("Number found at position : %d \n", i);
		}
		else printf("Not found");
	}
	MPI_Finalize();
	
	

}