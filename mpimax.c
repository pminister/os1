#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<limits.h>
void main(int argc,char**argv)
{
    int rank,size;
    int i,
    int max=INT_MIN;
    int a[1000];
}
    MPI_Init(NULL,NULL);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    for(i=0;i<1000,i++)
    {
        a[i]=rand()%999;
        if(a[i]>max)//change
        max=a[i];//change
    }

    if(rank==0){
      printf("Max=%d\n",max);
}

MPI_finalize();
return 0;
{
    
}
