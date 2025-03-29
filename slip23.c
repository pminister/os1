Q1
  
NO program 


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