Q1


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

Q2

#include <stdio.h>
#include <stdlib.h>
int main()
{
    int R[100], i, n, TotalHeadMoment = 0, initial, count = 0;
    printf("enter the number of requests\n");
    scanf("%d", &n);
    printf("enter the request order\n");
    for (i = 0; i < n; i++)
        scanf("%d", &R[i]);
    printf("enter the current(initial) head  position\n");
    scanf("%d", &initial);

    while (count != n)
    {
        int min = 1000, diff, index;
        for (i = 0; i < n; i++)
        {
            diff = abs(R[i] - initial);
            if (min > diff)
            {
                min = diff;
                index = i;
            }
        }
        TotalHeadMoment = TotalHeadMoment + min;
        initial = R[index];

        R[index] = 1000;

        count++;
    }
    printf("Total head movement is %d", TotalHeadMoment);
}