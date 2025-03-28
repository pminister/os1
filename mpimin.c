#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<limits.h>
void main(int argc,char**argv)
{
    int rank,size;
    int i;
    int min=INT_MIN;
    int a[1000];

    MPI_init(NULL,NULL);
    MPI_comm_rank(MPI_COMM_WORLD,&rank);
    MPI_comm_size(MPI_COMM_WORLD,&size);

    for(i=o;i<1000,i++)
    {
        a[i]=rand()%999;
        if(a[i]min)
        min=a[i];
    }

    if(rank==0)
    print("Min=%d\n",min);
}

MPI_finalize();
return 0;
{

}