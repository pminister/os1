Q1.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct file
{
    char name[10];
    int start;
    int size;
    int status;
} f[10];
struct node
{
    int info;
    char a[1];
    struct node *next;
    struct node *prev;
} *start, *temp, *new, *t, *s;

int fno = -1, sz, st, fb = 0;
char fn[10];

char name[10];
int size, d;
int i, ch;
void createBlock()
{
    printf("enter the total  block of disk:");
    scanf("%d", &d);
    start = temp = NULL;
    for (i = 0; i < d; i++)
    {
        new = (struct node *)malloc(sizeof(struct node));
        new->next = NULL;
        new->prev = NULL;
        strcpy(new->a, "F");
        new->info = i;
        if (start == NULL)
        {
            start = temp = new;
        }
        else
        {
            new->prev = temp;
            temp->next = new;
            temp = new;
        }
    }
}
void contains()
{
    temp = start;
    while (temp != NULL)
    {
        printf("%s\t", temp->a);
        temp = temp->next;
    }
}
void add()
{
    printf("Enter the file name and size:");
    scanf("%s%d", fn, &sz);
    fb = 0;
    temp = start;
    while (temp != NULL)
    {
        if (strcmp(temp->a, "A") == 0)
        {
            fb = 0;
        }
        if (strcmp(temp->a, "A") != 0)
        {
            if (fb == 0)
            {
                s = temp;
                fb++;
            }
            else
                fb++;
        }
        if (fb == sz)
        {
            break;
        }
        temp = temp->next;
    }
    if (fb < sz)
    {
        printf("\n Inefficient memory for file %s\n", fn);
        fb = 0;
    }
    else
    {
        fno++;
        strcpy(f[fno].name, fn);
        f[fno].size = sz;
        f[fno].start = s->info;
        f[fno].status = 1;
    }
    while (fb > 0)
    {
        strcpy(s->a, "A");
        s = s->next;
        fb--;
    }
}
void delete()
{
    printf("enter the file name to delete:\n");
    scanf("%s", fn);
    for (i = 0; i <= fno; i++)
    {
        if (strcmp(f[i].name, fn) == 0)
        {
            sz = f[i].size;
            st = f[i].start;
            f[i].status = 0;
            f[i].start = -1;
            break;
        }
    }
    temp = start;
    while (temp->next != NULL)
    {
        if (temp->info == st)
            break;
        else
            temp = temp->next;
    }
    while (sz > 0)
    {
        strcpy(temp->a, "F");
        temp = temp->next;
        sz--;
    }
}
void files()
{
    printf("\n--------------------------------------------------\n");
    printf("Fname\tSize\tStart\tstatus\n");
    printf("--------------------------------------------------\n");
    for (i = 0; i <= fno; i++)
    {
        if (f[i].status != 0)
            printf("%s\t%d\t%d\t%d\n", f[i].name, f[i].size, f[i].start, f[i].status);
    }
    printf("\n--------------------------------------------------\n");
}
void main()
{
    do
    {
        printf("1.create Block\n2.add \n3.Delete\n4.files\n5.cotians\n6.exit");
        printf("\n enter your choice");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            createBlock();
            break;
        case 2:
            add();
            break;
        case 3:
            delete ();
            break;
        case 4:
            files();
            break;
        case 5:
            contains();
            break;
        }
    } while (ch != 6);
}

Q2.

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