#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank,world,num,N;  // rank = each operation , num = ratio Elements/operations 
    N = 10;
    //num = N/world;  // N = Elements , World = operations 

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world);
    if (rank == 0){
        printf("Hello: rank %d, world: %d\n",rank, world);
        num = N/world;
        //MPI_Send();
        printf("\n I continue being Master Processor: Num for every Processing is  %d",num);
    }else{
        printf("\nW are the others\n %d", num);

    }
    //printf("Hello: rank %d, world: %d\n",rank, world);
    //printf("aytos einai enas arithmos %d\n",num);
    MPI_Finalize();
    
}