
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define ARRAY_SIZE 1000
int main(int argc, char** argv) {
int rank, size;
int numbers[ARRAY_SIZE];
int min_number = 0;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
if (rank == 0) {
// Generate random numbers for the root process
for (int i = 0; i < ARRAY_SIZE; i++) {
numbers[i] = rand() % 1000; // Generate random numbers between 0 and 999
}
}
// Scatter the array to all processes
MPI_Scatter(numbers, ARRAY_SIZE/size, MPI_INT, numbers, ARRAY_SIZE/size,
MPI_INT, 0, MPI_COMM_WORLD);
// Find the minimum number in the local array
int local_min = numbers[0];
for (int i = 1; i < ARRAY_SIZE/size; i++) {
if (numbers[i] < local_min) {
local_min = numbers[i];
}
}
// Reduce all the local minimums to find the global minimum
MPI_Reduce(&local_min, &min_number, 1, MPI_INT, MPI_MIN, 0,
MPI_COMM_WORLD);
if (rank == 0) {
printf("The minimum number is: %d\n", min_number);
}
MPI_Finalize();
return 0;
}
