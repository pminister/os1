#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
int main(int argc,char**argv){
    int rank,size;
    int i, sum=0;
    int a[1000];

    MPI_Init(NULL,NULL);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    for(i=0;i<1000,i++) {

        a[i]=rand()%999;
        sum+=a[i];
    }

    if(rank==0){
      printf("sum=%d\n",sum);
}

MPI_finalize();
return 0;
{   
}
}


