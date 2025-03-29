Q.1 ) Write a C Menu driven Program to implement following functionality
a) Accept Available
b) Display Allocation, Max
c) Display the contents of need matrix
d) Display Available
eecrfHY
#include <stdio.h>
void main()
{
    int n, m, alloc[10][10], max[10][10], avai[10], need[10][10], i, j, work[10], finish[10], proc = -1, flag = 1;
    printf("Enter the number of Process :");
    scanf("%d", &n);
    printf("Enter the number of resources :");
    scanf("%d", &m);
    printf("Enter the allocation matrix:\n ");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }
    printf("Enter maximum matrix :\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }
    printf("enter the available matrix:\n");
    for (i = 0; i < m; i++)
    {
        scanf("%d", &avai[i]);
    }
    printf("allocation matrix is :\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("%d\t", alloc[i][j]);
        }

        printf("\n");
    }

    printf("maximum matrix is :\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("%d\t", max[i][j]);
        }
        printf("\n");
    }

    printf("Available matrix is :\n");
    for (i = 0; i < m; i++)
    {
        printf("%d\t", avai[i]);
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    printf("\nneed matrix is :\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("%d\t", need[i][j]);
        }
        printf("\n");
    }
}

Q.2 Write a simulation program for disk scheduling using FCFS algorithm. Accept
total number of disk blocks, disk request string, and current head position from the
user. Display the list of request in the order in which it is served. Also display the
total number of head moments.
55, 58, 39, 18, 90, 160, 150, 38, 184
Start Head Position: 50

#include<math.h> 
#include<stdio.h> 
#include<stdlib.h> 
int main() 
{ 
int i,n,req[50],mov=0,cp;
 printf("enter the current(initial) head  position\n"); 
 scanf("%d",&cp); 
 printf("enter the number of requests\n"); 
 scanf("%d",&n); 
 printf("enter the request order\n");
  for(i=0;i<n;i++) 
  { 
  scanf("%d",&req[i]);
   } 
   mov=mov+abs(cp-req[0]); 
   // abs is used to calculate the absolute value 
  
   for(i=1;i<n;i++)
    { 
    mov=mov+abs(req[i]-req[i-1]);
    
     } 
     printf("\n"); 
     printf("total head movement = %d\n",mov); 
     }
     
     
     
     
     
     
     
     
     
     
     
     
     
     
