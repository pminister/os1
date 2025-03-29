Q.1 Write a program to simulate Linked file allocation method. Assume disk with n
number of blocks. Give value of n as input. Randomly mark some block as allocated and
accordingly maintain the list of free blocks Write menu driver program with menu
options as mentioned below and implement each option.
• Show Bit Vector
• Create New File
• Show Directory
• Exit

#include <stdio.h>
struct node
{
    int data;
    struct node *next;

} *newnode, *temp, *start, *temp1;
int m, n, i, x;

void create()
{
    i = 0;
    start = NULL;
    while (i != n)
    {
        newnode = (struct node *)malloc(sizeof(struct node));
        newnode->next = NULL;
        newnode->data = -1;
        if (start == NULL)
            start = temp = newnode;
        else
        {
            temp->next = newnode;
            temp = newnode;
        } // else
        i++;
    } // while

} // create

void allocate()
{
    int count = 0;
    temp1 = start;

    if (temp1->data == -1)
    {

        if (m <= n)
        {
            for (i = 0; i < m - 1; i++)
            {
                temp1->data = 0;
                temp1 = temp1->next;
            }
            temp1->data = -2; // end of file
        } // if
        else
        {
            printf("\nBlocks can not be allocated");
            exit(0);
        }
    } // if
    else
    {
        while (temp1->data != -1)
        {
            temp1 = temp1->next;
            count++;
        }
        if (m + count <= n)
        {
            for (i = 0; i < m - 1; i++)
            {
                temp1->data = 0;
                temp1 = temp1->next;
            } // for
            temp1->data = -2; // end of file
        } // if
        else
        {
            printf("\nBlocks can not be allocated");
            exit(0);
        }
    } // else

} // allocate

void deallocate()
{
    int count = 0;
    temp1 = start;
    while (count != x - 1)
    {
        temp1 = temp1->next;
        if (temp1->data == -2)
            count++;
    } // while

    while (temp1->data != -2)
    {
        temp1->data = -1;
        temp1 = temp1->next;

    } // while*/
    temp1->data = -1;

} // deallocate

void display()
{
    int tot = 0;
    temp1 = start;
    while (temp1 != NULL)
    {
        printf("%d\t", temp1->data);
        if (temp1->data == -1)
            tot++;
        temp1 = temp1->next;
    } // while
    printf("\nTotal allocated blocks are %d", n - tot);
    printf("\nTotal free blocks are %d", tot);
}
void main()
{
    int ch;
    while (1)
    {
        printf("\n1:Create\n");
        printf("2:Add new\n");
        printf("3:Deallocate\n");
        printf("4:Display\n");
        printf("5:Exit\n");
        printf("\nEnter your choice");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("Enter the size of disk");
            scanf("%d", &n);
            create();
            break;
        case 2:
            printf("Enter the number of blocks to be allocated");
            scanf("%d", &m);
            allocate();
            break;
        case 3:
            printf("Enter the block to delete\n");
            scanf("%d", &x);
            deallocate();
            break;
        case 4:
            display();
            break;
        case 5:
            exit(0);
        } // switch
    } // while
} // main


Q.2 Write an MPI program to calculate sum of randomly generated 1000 numbers
(stored in array) on a cluster

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char **argv) {
    int rank, size;
    int i, local_sum = 0, global_sum = 0;
    int arr[ARRAY_SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Seed the random number generator differently on each process
    srand(42 + rank); // Ensure different seeds

    // Generate random numbers and compute local sum
    for (i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = rand() % 100;
        local_sum += arr[i];
    }

    // Reduce local sums to a global sum
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Total sum of array elements across all processes = %d\n", global_sum);
    }

    MPI_Finalize();

    return 0;
}