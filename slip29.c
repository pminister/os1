Q1
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

int main(int argc, char *argv[])
{
    int rank, size;
    int numbers[SIZE], local_sum = 0, total_sum = 0;
    int chunk_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    chunk_size = SIZE / size; // Each process handles an equal portion

    int *sub_array = (int *)malloc(chunk_size * sizeof(int));

    if (rank == 0)
    {
        srand(time(NULL));
        for (int i = 0; i < SIZE; i++)
        {
            numbers[i] = rand() % 1000; // Generate random numbers (0-999)
        }
        printf("Generated numbers: \n");
        for (int i = 0; i < SIZE; i++)
        {
            printf("%d ", numbers[i]);
        }
        printf("\n");
    }

    // Scatter data to all processes
    MPI_Scatter(numbers, chunk_size, MPI_INT, sub_array, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Calculate local sum of even numbers
    for (int i = 0; i < chunk_size; i++)
    {
        if (sub_array[i] % 2 == 0)
        {
            local_sum += sub_array[i];
        }
    }

    // Reduce to get the total sum at root process
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("Total sum of even numbers: %d\n", total_sum);
    }

    free(sub_array);
    MPI_Finalize();
    return 0;
}

Q2.

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