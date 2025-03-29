Q.1 Consider a system with ‘m’ processes and ‘n’ resource types. Accept number of
instances for every resource type. For each process accept the allocation and maximum
requirement matrices. Write a program to display the contents of need matrix and to
check if the given request of a process can be granted immediately or not

Q.2 Write an MPI program to find the max number from randomly generated 1000 numbers
(stored in array) on a cluster (Hint: Use MPI_Reduce)

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define NUM_NUMBERS 10000

int main(int argc, char *argv[]) {
    int rank, size;
    int numbers[NUM_NUMBERS];
    int local_min, local_max;
    int global_min, global_max;

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Seed random number generator differently for each process
    srand(time(NULL) + rank);

    // Generate random numbers (only for rank 0 for simplicity)
    if (rank == 0) {
        for (int i = 0; i < NUM_NUMBERS; i++) {
            numbers[i] = rand() % 10000;  // Random numbers between 0 and 999
        }
    }

    // Distribute numbers to all processes
    int num_per_process = NUM_NUMBERS / size;
    int local_numbers[num_per_process];
    MPI_Scatter(numbers, num_per_process, MPI_INT, local_numbers, num_per_process, MPI_INT, 0, MPI_COMM_WORLD);

    // Find local min and max
    local_min = local_numbers[0];
    local_max = local_numbers[0];
    for (int i = 0
    ; i < num_per_process; i++) {
        if (local_numbers[i] < local_min) {
            local_min = local_numbers[i];
        }
        if (local_numbers[i] > local_max) {
            local_max = local_numbers[i];
        }
    }

    // Reduce to find global min and max
    MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    // Rank 0 will print the results
    if (rank == 0) {
        printf("Minimum value: %d\n", global_min);
        printf("Maximum value: %d\n", global_max);
    }

    // Finalize MPI
    MPI_Finalize();
    return 0;
}

