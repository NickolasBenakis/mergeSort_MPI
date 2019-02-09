#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, world, num, N, target; // rank = each operation , num = ratio Elements/operations
    N = 12;
    //num = N/world;  // N = Elements , World = operations
    MPI_Status status;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world);
    if (rank == 0)
    {
        num = N / world;  // I set the num in the master processor
        printf("\n Master rank %d, world: %d, num: %d\n", rank, world, num); // I print data for the master
        
        for (target = 1; target < world; target++) // I make a loop in order to send in each other processor the load
        {
            MPI_Send(&num, 1, MPI_INT, target, 10, MPI_COMM_WORLD);
        }
    }
    else // everyone else receives the load from Master
    {
        MPI_Recv(&num, 1, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
        printf("\n Slave %d, num: %d\n", rank, num);
    }
    //printf("Hello: rank %d, world: %d\n",rank, world);
    //printf("aytos einai enas arithmos %d\n",num);
    MPI_Finalize();
}