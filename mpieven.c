#include <stdio.h> 
#include <stdlib.h> 
#include <mpi.h> 
int main(int argc, char **argv) { 
 int rank, size; 
 int i, even = 0; 
 int a[1000]; 
 MPI_Init(NULL, NULL); 
 MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
 MPI_Comm_size(MPI_COMM_WORLD, &size); 
 for(i = 0; i < 1000; i++) { 
 a[i] = rand() % 999; 
 if(a[i] % 2 == 0) 
 even += a[i]; // Sum of even numbers 
 } 
 if(rank == 0) { 
 prinƞ("Sum of Even Numbers = %d\n", even); 
 } 
 MPI_Finalize(); 
 return 0; 
}