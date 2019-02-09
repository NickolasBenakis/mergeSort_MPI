#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);
    int rank;
    int world;
    int arithmos = 666;
    float arithmos2 = 66.66;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world);
    printf("Hello: rank %d, world: %d\n",rank, world);
    printf("aytos einai enas arithmos %f\n",arithmos2);
    MPI_Finalize();
    
}