Q1

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
