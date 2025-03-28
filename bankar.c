#include <stdio.h>

void main()
{
  int n,m,i,j,k,proc=-1,flag=1,rpn,grant=1,f=0;
  printf("Enter the number of processes: ");
  scanf("%d",&n);
  printf("Enter the number of resources: ");
  scanf("%d",&m);
  int allocation[n][m], max[n][m], available[m], need[n][m], finish[n], work[m], sequence[n], request[m];

  printf("Enter the allocation matrix: ");
  for(i=0; i<n; i++)
    for(j=0; j<m; j++)
      scanf("%d",&allocation[i][j]);

  printf("\n*** Allocation Matrix ***\n");
  for(i=0; i<n; i++)
  {
    for(j=0; j<m; j++)
      printf("\t%d",allocation[i][j]);
    printf("\n");
  }

  printf("\nEnter the max matrix: ");
  for(i=0; i<n; i++)
    for(j=0; j<m; j++)
      scanf("%d",&max[i][j]);

  printf("\n*** Max Matrix ***\n");
  for(i=0; i<n; i++)
  {
    for(j=0; j<m; j++)
      printf("\t%d",max[i][j]);
    printf("\n");
  }

  printf("\nEnter the available matrix: ");
  for(i=0; i<m; i++)
  {
    scanf("%d",&available[i]);
    work[i]=available[i];
  }

  printf("\n*** Available Matrix ***\n");
  for(i=0; i<m; i++)
    printf("\t%d",available[i]);
  printf("\n\n");

  printf("\nIs there any request?[1/0] : ");
  scanf("%d",&f);
  if(f)
  {
    printf("\nEnter Process no : ");
    scanf("%d",&rpn);
    printf("\nEnter request : ");
    for(i=0; i<m; i++)
      scanf("%d",&request[i]);

    printf("\n*** Request Matrix for Process P%d ***\n",rpn);
    for(i=0; i<m; i++)
      printf("\t%d",request[i]);
    printf("\n");
  }

  // calculating need matrix
  for(i=0; i<n; i++)
    for(j=0; j<m; j++)
      need[i][j]=max[i][j]-allocation[i][j];

  // printing need matrix
  printf("\n*** Need Matrix ***\n");
  for(i=0; i<n; i++)
  {
    for(j=0; j<m; j++)
      printf("\t%d",need[i][j]);
    printf("\n");
  }

  for(i=0; i<n; i++)
    finish[i]=0;

  // Banker's Algorithm
  outer: 
  for(i=0; i<n; i++)
  {
    if(finish[i]==0)
    {
      for(j=0; j<m; j++)
      {
        if(need[i][j] > work[j])
          flag=0;
      }
      if(flag==0)
        printf("\nProcess P%d must wait!\nResource not available...",i);
      else
      {
        printf("\nProcess P%d safe",i);
        finish[i]=1;
        sequence[++proc] = i;
        for(k=0; k<m; k++)
           work[k]=work[k]+allocation[i][k];
      }
      flag=1;
    }
  }
  
  for(i=0; i<n; i++)
    if(finish[i]==0)
      goto outer;

  printf("\n*** Safe Sequence ***\n");
  for(i=0; i<n; i++)
    printf("\tP%d",sequence[i]);
  printf("\n\n");
}