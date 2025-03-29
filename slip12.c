Q1
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char **argv)
{
    int rank, size;
    int i, local_sum = 0, global_sum = 0;
    int arr[ARRAY_SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Seed the random number generator differently on each process
    srand(42 + rank); // Ensure different seeds

    // Generate random numbers and compute local sum
    for (i = 0; i < ARRAY_SIZE; i++)
    {
        arr[i] = rand() % 100;
        local_sum += arr[i];
    }

    // Reduce local sums to a global sum
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("Total sum of array elements across all processes = %d\n", global_sum);
    }

    MPI_Finalize();

    return 0;
}

Q2


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

        // change
        /*TotalHeadMoment += abs(size -  RQ[i-1]-1);
        TotalHeadMoment += abs(size - 1-0);
        initial =0;*/
        for (i = 0; i < index; i++)
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
        // change
        /*
        TotalHeadMoment += abs( RQ[i+1]-0);
        TotalHeadMoment += abs( size-1-0);
        initial = size-1;*/
        for (i = n - 1; i >= index; i--)
        {
            TotalHeadMoment += abs(RQ[i] - initial);
            initial = RQ[i];
        }
    }
    printf("Total head movement is: %d\n", TotalHeadMoment);
    return 0;
}
