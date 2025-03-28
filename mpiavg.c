#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
void main(int argc,char**argv)
{
    int rank,size;   
    int i,sum=0;
    float avg;//change
    int a[1000];

MPI_Init(NULL_NULL);
MPI_comm_rank(MPI_COMM_WORLD,&rank);
MPI_comm_size(MPI_COMM_WORLD,&size);

for(i=0,i<1000,i++){
    a[i]=rand()%999;
    sum+=a[i];
}

    avg=(float)sum/1000;//change
  if(rank==0)
  {
  printf("average=%.2f,\n",avg);

  }

MPI_finalize();
return 0;
}
