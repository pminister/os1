Q1

#include <stdio.h>
struct node
{
    int data;
    struct node *next;

} *newnode, *temp, *start, *temp1;
int m, n, i, x, no, a;
int dir[10][2];
a = 0;
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
    int cnt = 1;
    int count = 0;

    temp1 = start;

    if (temp1->data == -1)
    {

        if (m <= n)
        {
            temp1->data = cnt;
            temp1 = temp1->next;
            for (i = 1; i < m - 1; i++)
            {
                temp1->data = 0;
                temp1 = temp1->next;
                // cnt++;
            }
            temp1->data = -2; // end of file
            // cnt++;
            dir[a][0] = no;
            dir[a][1] = cnt;
            a++;
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
            count++; // count no of allocated blocks
            cnt++;
        }
        if (m + count <= n) // check available blocks
        {
            temp1->data = cnt;
            for (i = 1; i < m - 1; i++)
            {
                temp1 = temp1->next;
                temp1->data = 0;

                // cnt++;
            } // for
            temp1 = temp1->next;
            temp1->data = -2; // end of file
            dir[a][0] = no;
            dir[a][1] = cnt;
            a++;
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
    int bno, j;
    int count = 1;
    temp1 = start;
    for (j = 0; j < 10; j++)
    {
        if (dir[j][0] == x)
        {
            bno = dir[j][1];
            dir[j][0] = 0;
            dir[j][1] = 0;
            break;
        }
    } // for
    while (count != bno)
    {
        count++;
        temp1 = temp1->next;
        // if(temp1->data==-2)
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
    printf("\nTotal free blocks are %d\n", tot);
    for (i = 0; i < 10; i++)
    {
        printf("%d\t%d", dir[i][0], dir[i][1]);
        printf("\n");
    } // for
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
            printf("\nEnter the file number to allocate\n");
            scanf("%d", &no);
            printf("\nEnter the number of blocks to be allocated");
            scanf("%d", &m);
            allocate();
            break;
        case 3:
            printf("\nEnter the file number to delete\n");
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

Q2

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