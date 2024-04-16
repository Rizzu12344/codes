#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define ARRAY_SIZE 1000
int main(int argc, char *argv[]) {
int rank, size;
int i;
int local_sum = 0;
double local_avg = 0.0;
int total_sum = 0;
double total_avg = 0.0;
int numbers[ARRAY_SIZE];
int local_sums[size]; // Array to store local sums of each process
double local_avgs[size]; // Array to store local averages of each process
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
if (rank == 0) {
// Generate random numbers
for (i = 0; i < ARRAY_SIZE; i++) {
numbers[i] = rand() % 100;
}
}
// Scatter the numbers to all processes
MPI_Scatter(numbers, ARRAY_SIZE / size, MPI_INT, numbers, ARRAY_SIZE / size,
MPI_INT, 0, MPI_COMM_WORLD);
// Calculate local sum and average
for (i = 0; i < ARRAY_SIZE / size; i++) {
local_sum += numbers[i];
}
local_avg = (double)local_sum / (ARRAY_SIZE / size);
// Gather all local sums and averages to process 0
MPI_Gather(&local_sum, 1, MPI_INT, local_sums, 1, MPI_INT, 0,
MPI_COMM_WORLD);
MPI_Gather(&local_avg, 1, MPI_DOUBLE, local_avgs, 1, MPI_DOUBLE, 0,
MPI_COMM_WORLD);
// Calculate total sum and average on process 0
if (rank == 0) {
for (i = 0; i < size; i++) {
total_sum += local_sums[i];
total_avg += local_avgs[i];
}
total_avg /= size;
printf("Total sum of 1000 random numbers: %d\n", total_sum);
printf("Average of 1000 random numbers: %.2f\n", total_avg);
}
MPI_Finalize();
return 0;
}
