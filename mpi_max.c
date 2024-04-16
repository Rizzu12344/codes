#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define SIZE 1000
int main(int argc, char** argv) {
int rank, size;
int numbers[SIZE];
int max_number = 0;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
if (rank == 0) {
// Generate random numbers for the root process
for (int i = 0; i < SIZE; i++) {
numbers[i] = rand() % 1000; // Generate numbers between 0 and 999
}
}
// Scatter the numbers to all processes
MPI_Bcast(numbers, SIZE, MPI_INT, 0, MPI_COMM_WORLD);
// Find the local maximum
for (int i = 0; i < SIZE; i++) {
if (numbers[i] > max_number) {
max_number = numbers[i];
}
}
// Reduce to find the global maximum
int global_max_number;
MPI_Reduce(&max_number, &global_max_number, 1, MPI_INT, MPI_MAX, 0,MPI_COMM_WORLD);
if (rank == 0) {
printf("The maximum number is: %d\n", global_max_number);
}
MPI_Finalize();
return 0;
}
