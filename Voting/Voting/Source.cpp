#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {

	int rank, currentVote = -2, leadingVote = -1;
	int world_size, sender, receiver;
	int leader = -3;
	

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	if (rank == 0)
		sender = world_size - 1;
	else sender = rank - 1;

	if (rank == world_size - 1)
		receiver = 0;
	else receiver = rank + 1;


	srand(time(NULL) + rank);
	currentVote = rand() % 100 + 1;

	MPI_Barrier(MPI_COMM_WORLD);

	printf("Process %d has voted as: %d \n", rank, currentVote);

	if (rank != 0) {
		MPI_Recv(&leadingVote, 1, MPI_INT, sender, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		printf("Process %d received vote %d from process %d\n", rank, leadingVote, sender);

		if (leadingVote > currentVote) {
			leader = leadingVote;
			MPI_Send(&leadingVote, 1, MPI_INT, receiver, 0, MPI_COMM_WORLD);
			printf("Process %d sent vote %d to process %d\n", rank, leadingVote, receiver);
		}
		else {
			MPI_Send(&currentVote, 1, MPI_INT, receiver, 0, MPI_COMM_WORLD);
			printf("Process %d sent vot %d to process %d\n", rank, currentVote, receiver);
		}
	}
	else {
		leader = currentVote;
		MPI_Send(&currentVote, 1, MPI_INT, receiver, 0, MPI_COMM_WORLD);
		printf("Process %d sent vote %d  to process %d\n", rank, currentVote, receiver);

		MPI_Recv(&leadingVote, 1, MPI_INT, sender, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		printf("Process %d received vote %d from process %d\n", rank, leadingVote, sender);
		if (leadingVote > currentVote) {
			leader = leadingVote;
			MPI_Send(&currentVote, 1, MPI_INT, receiver, 0, MPI_COMM_WORLD);
			printf("Process %d sent vote %d  to process %d\n", rank, leadingVote, receiver);
		}
		
	}

	MPI_Barrier(MPI_COMM_WORLD);

	MPI_Finalize();

	if (rank == 0)
		printf("Leader is %d", leader);

	return 0;
}