#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);
    int rank,world,num,N;  // rank = each operation , num = ratio Elements/operations 

    num = N/world;  // N = Elements , World = operations 

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world);
    printf("Hello: rank %d, world: %d\n",rank, world);
    printf("aytos einai enas arithmos %f\n",arithmos2);
    MPI_Finalize();
    
}