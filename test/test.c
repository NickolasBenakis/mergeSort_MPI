#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
// int main(int argc, char **argv)
// {
//     MPI_Init(&argc, &argv);
//     int rank, world, num, N, target,n; // rank = each operation , num = ratio Elements/operations
//     N = 12;
    
//     //num = N/world;  // N = Elements , World = operations
//     MPI_Status status;
//     int values[] = {8,2,3,5,6};
//     int cmpfunc (const void * a, const void * b) {
//     return ( *(int*)a - *(int*)b );
//     }
    
//     printf("Before sorting the list is: \n");
//     for( n = 0 ; n < 5; n++ ) {
//         printf("%d ", values[n]);
//     }

//     qsort(values,5,sizeof(int),cmpfunc );

//     printf("\nAfter sorting the list is: \n");
//     for( n = 0 ; n < 5; n++ ) {   
//         printf("%d ", values[n]);
//     }
//     return (0);
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//     MPI_Comm_size(MPI_COMM_WORLD, &world);
    
//     MPI_Finalize();
// }


int values[] = { 88, 56, 100, 2, 25 };

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int main () {
    int n;

    printf("Before sorting the list is: \n");
    for( n = 0 ; n < 5; n++ ) {
        printf("%d ", values[n]);
    }

    qsort(values, 5, sizeof(int), cmpfunc);

    printf("\nAfter sorting the list is: \n");
    for( n = 0 ; n < 5; n++ ) {   
    printf("%d ", values[n]);
    }

    return(0);
}