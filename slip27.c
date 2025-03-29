Q1
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int RQ[100], i, j, n, TotalHeadMoment = 0, initial, size, move, index;
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    printf("Enter the request sequence: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &RQ[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &initial);
    printf("Enter the total disk size: ");
    scanf("%d", &size);
    printf("Enter the head movement direction 1 for high, 0 for low: ");
    scanf("%d", &move);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (RQ[j] > RQ[j + 1])
            {
                int temp = RQ[j];
                RQ[j] = RQ[j + 1];
                RQ[j + 1] = temp;
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        if (initial < RQ[i])
        {
            index = i;
            break;
        }
    }
    if (move == 1)
    {
        for (i = index; i < n; i++)
        {
            TotalHeadMoment += abs(RQ[i] - initial);
            initial = RQ[i];
        }
        /*TotalHeadMoment += abs(size - 1 - RQ[i-1]);
        initial = size - 1;*/
        for (i = index - 1; i >= 0; i--)
        {
            TotalHeadMoment += abs(RQ[i] - initial);
            initial = RQ[i];
        }
    }
    else
    {
        for (i = index - 1; i >= 0; i--)
        {
            TotalHeadMoment += abs(RQ[i] - initial);
            initial = RQ[i];
        }
        /*TotalHeadMoment += abs(0 - RQ[i+1]);
        initial = 0;*/
        for (i = index; i < n; i++)
        {
            TotalHeadMoment += abs(RQ[i] - initial);
            initial = RQ[i];
        }
    }
    printf("Total head movement is: %d\n", TotalHeadMoment);
    return 0;
}

Q2


#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define NUM_NUMBERS 10000

int main(int argc, char *argv[])
{
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
    if (rank == 0)
    {
        for (int i = 0; i < NUM_NUMBERS; i++)
        {
            numbers[i] = rand() % 10000; // Random numbers between 0 and 999
        }
    }

    // Distribute numbers to all processes
    int num_per_process = NUM_NUMBERS / size;
    int local_numbers[num_per_process];
    MPI_Scatter(numbers, num_per_process, MPI_INT, local_numbers, num_per_process, MPI_INT, 0, MPI_COMM_WORLD);

    // Find local min and max
    local_min = local_numbers[0];
    local_max = local_numbers[0];
    for (int i = 0; i < num_per_process; i++)
    {
        if (local_numbers[i] < local_min)
        {
            local_min = local_numbers[i];
        }
        if (local_numbers[i] > local_max)
        {
            local_max = local_numbers[i];
        }
    }

    // Reduce to find global min and max
    MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    // Rank 0 will print the results
    if (rank == 0)
    {
        printf("Minimum value: %d\n", global_min);
        printf("Maximum value: %d\n", global_max);
    }

    // Finalize MPI
    MPI_Finalize();
    return 0;
}
