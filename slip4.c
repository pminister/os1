Q.1 Implement the Menu driven Banker algorithm for accepting Allocation, Max
from user.

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

Q.2 Write a simulation program for disk scheduling using SCAN algorithm. Accept total
number of disk blocks, disk request string, and current head position from the user.
Display the list of request in the order in which it is served. Also display the total
number of head moments.
86, 147, 91, 170, 95, 130, 102, 70
Starting Head position= 125
Direction: Left

#include <stdio.h>
#include <stdlib.h>
int main()
{
    int RQ[100], i, j, n, TotalHeadMoment = 0, initial, size, move;
    printf("Enter the number of Requests\n");
    scanf("%d", &n);
    printf("Enter the Requests sequence\n");
    for (i = 0; i < n; i++)
        scanf("%d", &RQ[i]);
    printf("Enter initial head position\n");
    scanf("%d", &initial);
    printf("Enter total disk size\n");
    scanf("%d", &size);
    printf("Enter the head movement direction for high 1 and for low 0\n");
    scanf("%d", &move);

    // logic for Scan disk scheduling

    /*logic for sort the request array */
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (RQ[j] > RQ[j + 1])
            {
                int temp;
                temp = RQ[j];
                RQ[j] = RQ[j + 1];
                RQ[j + 1] = temp;
            }
        }
    }

    int index;
    for (i = 0; i < n; i++)
    {
        if (initial < RQ[i])
        {
            index = i;
            break;
        }
    }

    // if movement is towards high value
    if (move == 1)
    {
        for (i = index; i < n; i++)
        {
            TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - initial);
            initial = RQ[i];
        }
        //  last movement for max size
        TotalHeadMoment = TotalHeadMoment + abs(size - RQ[i - 1] - 1);
        initial = size - 1;
        for (i = index - 1; i >= 0; i--)
        {
            TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - initial);
            initial = RQ[i];
        }
    }
    // if movement is towards low value
    else
    {
        for (i = index - 1; i >= 0; i--)
        {
            TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - initial);
            initial = RQ[i];
        }
        //  last movement for min size
        TotalHeadMoment = TotalHeadMoment + abs(RQ[i + 1] - 0);
        initial = 0;
        for (i = index; i < n; i++)
        {
            TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - initial);
            initial = RQ[i];
        }
    }

    printf("Total head movement is %d", TotalHeadMoment);
    return 0;
}

