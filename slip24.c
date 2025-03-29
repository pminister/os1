Q1.

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

// Function to generate random numbers in an array
void generate_random_numbers(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 1000; // Random number between 0 and 999
    }
}

// Function to calculate sum of odd numbers
int sum_of_odds(int *arr, int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] % 2 != 0)
        {
            sum += arr[i];
        }
    }
    return sum;
}

int main(int argc, char *argv[])
{
    int rank, size;
    int numbers[SIZE];
    int local_sum = 0, total_sum = 0;
    int chunk_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    chunk_size = SIZE / size; // Divide array among processes
    int *sub_array = (int *)malloc(chunk_size * sizeof(int));

    if (rank == 0)
    {
        srand(time(NULL));
        generate_random_numbers(numbers, SIZE);
        printf("Generated numbers: ");
        for (int i = 0; i < SIZE; i++)
        {
            printf("%d ", numbers[i]);
        }
        printf("\n");
    }

    // Distribute parts of the array to all processes
    MPI_Scatter(numbers, chunk_size, MPI_INT, sub_array, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process calculates the sum of its odd numbers
    local_sum = sum_of_odds(sub_array, chunk_size);

    // Reduce local sums into total_sum at the root process
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("Total sum of odd numbers: %d\n", total_sum);
    }

    free(sub_array);
    MPI_Finalize();
    return 0;
}

Q2.


#include <stdio.h>

void main()
{
    int n, m, i, j, k, proc = -1, flag = 1, rpn, grant = 1, f = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);
    int allocation[n][m], max[n][m], available[m], need[n][m], finish[n], work[m], sequence[n], request[m];

    printf("Enter the allocation matrix: ");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    printf("\n*** Allocation Matrix ***\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            printf("\t%d", allocation[i][j]);
        printf("\n");
    }

    printf("\nEnter the max matrix: ");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("\n*** Max Matrix ***\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            printf("\t%d", max[i][j]);
        printf("\n");
    }

    printf("\nEnter the available matrix: ");
    for (i = 0; i < m; i++)
    {
        scanf("%d", &available[i]);
        work[i] = available[i];
    }

    printf("\n*** Available Matrix ***\n");
    for (i = 0; i < m; i++)
        printf("\t%d", available[i]);
    printf("\n\n");

    printf("\nIs there any request?[1/0] : ");
    scanf("%d", &f);
    if (f)
    {
        printf("\nEnter Process no : ");
        scanf("%d", &rpn);
        printf("\nEnter request : ");
        for (i = 0; i < m; i++)
            scanf("%d", &request[i]);

        printf("\n*** Request Matrix for Process P%d ***\n", rpn);
        for (i = 0; i < m; i++)
            printf("\t%d", request[i]);
        printf("\n");
    }

    // calculating need matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    // printing need matrix
    printf("\n*** Need Matrix ***\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            printf("\t%d", need[i][j]);
        printf("\n");
    }

    for (i = 0; i < n; i++)
        finish[i] = 0;

// Banker's Algorithm
outer:
    for (i = 0; i < n; i++)
    {
        if (finish[i] == 0)
        {
            for (j = 0; j < m; j++)
            {
                if (need[i][j] > work[j])
                    flag = 0;
            }
            if (flag == 0)
                printf("\nProcess P%d must wait!\nResource not available...", i);
            else
            {
                printf("\nProcess P%d safe", i);
                finish[i] = 1;
                sequence[++proc] = i;
                for (k = 0; k < m; k++)
                    work[k] = work[k] + allocation[i][k];
            }
            flag = 1;
        }
    }

    for (i = 0; i < n; i++)
        if (finish[i] == 0)
            goto outer;

    printf("\n*** Safe Sequence ***\n");
    for (i = 0; i < n; i++)
        printf("\tP%d", sequence[i]);
    printf("\n\n");

    // Checking Request for grantable or not
    for (i = 0; i < m; i++)
        if (request[i] > need[rpn][i] | request[i] > available[i])
        {
            grant = 0;
            break;
        }

    if (grant == 1)
    {
        printf("\nRequest P%d can be granted immediately\n\n", rpn);
        for (i = 0; i < m; i++)
        {
            available[i] = available[i] - request[i];
            allocation[rpn][i] = allocation[rpn][i] + request[i];
            need[rpn][i] = need[rpn][i] - request[i];
            work[i] = available[i];
        }
        for (i = 0; i < n; i++)
            finish[i] = 0;
        flag = 1;
        proc = -1;

    // Banker's Algorithm
    outer2:
        for (i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                        flag = 0;
                }
                if (flag == 0)
                    printf("\nProcess P%d must wait!\nResource not available...\n", i);
                else
                {
                    printf("\nProcess P%d added", i);
                    finish[i] = 1;
                    sequence[++proc] = i;
                    for (k = 0; k < m; k++)
                        work[k] = work[k] + allocation[i][k];
                }
                flag = 1;
            }
        }

        for (i = 0; i < n; i++)
            if (finish[i] == 0)
                goto outer2;

        printf("\n*** New Safe Sequence ***\n");
        for (i = 0; i < n; i++)
            printf("\tP%d", sequence[i]);
        printf("\n\n");
    }
    else
        printf("\nRequest P%d cannot be granted immediately\n\n", rpn);
}
