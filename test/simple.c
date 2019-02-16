#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
     *  You can simply compile and run this script using:
     *  - mpicc main.c -o out && mpirun -np 4 out 24
     * */

//order of holding keys
int getOrder( int myBoundaries[2], int hisBoundaries[2], int myRank, int hisRank){
    int myMin = myBoundaries[0];
    int myMax = myBoundaries[1];
    int hisMin = hisBoundaries[0];
    int hisMax = hisBoundaries[1];

    if( myMin < hisMin){
        return -1;
    }
    if( myMin > hisMin){
        return 1;
    }
    if( myMax > hisMax){
        return 1;
    }
    if (myMax < hisMax){
        return -1;
    }
    if( myMin == hisMin && myMax == hisMax){

        if(myRank == hisRank){
            return -1;
        } else {
            return 1;
        }
    }
    return 0;
}



int cmpfunc(const void *, const void *);

int main(int argc, const char *argv[])
{
    int n = 8;
    int original_array[] = { 16, 13, 10, 8, 9 , 15, 2, 4 };    
    int rank, size, num, startTime, endTime, finalTime, tag;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

        // Step 1 : I set a list with n items
    if (rank == 0){
    printf("\nOriginal Array\n");
    for (int i = 0; i < n; i++)
    {
        //original_array[i] = rand() % (2 * n);
        printf("%d, ", original_array[i]);
    }
    printf("\n");
    }


    num = n / size;
    int sub_array[num], first, last, middle, splitter, median,median_first, search, min0,max0,min1,max1,min,max, msgtag;
    
    MPI_Scatter(original_array, num, MPI_INT,
                sub_array, num, MPI_INT,
                0, MPI_COMM_WORLD);

    qsort(sub_array, num, sizeof(int), cmpfunc);

    printf("\nSorted Array: \n");
    for (int i = 0; i < num; i++)
    {
        printf("%d ", sub_array[i]);
    }
    printf("\n");

    // Step 2.2: Exchange boundary values between paired groups

    // thetw local min,max se ena array boundaries
    int my_bound[] = { sub_array[0], sub_array[num-1]}; // ayta tha exw local
    int send_bound[] = { sub_array[0], sub_array[num-1]}; // ayta tha steilw
    if ( rank == 0){
        for(int i=0;i<2;i++){
            printf("\n boundaries tou rank 0 : %d \n",my_bound[i]);
        }
    }else if ( rank == 1 ){
        for(int i=0;i<2;i++){
            printf("\n boundaries tou rank 1 : %d \n",my_bound[i]);
        }     
    }


    if ( rank == 0 ){
        MPI_Send(&send_bound,1,MPI_INT,1,msgtag, MPI_COMM_WORLD);
        MPI_Recv(&send_bound,1,MPI_INT,1,msgtag,MPI_COMM_WORLD,&status);


    }else if ( rank == 1) {
        MPI_Send(&send_bound,1,MPI_INT,0,msgtag, MPI_COMM_WORLD);
        MPI_Recv(&send_bound,1,MPI_INT,0,msgtag,MPI_COMM_WORLD,&status);
    }

    if( rank == 0){
        for(int i=0;i<2;i++){
            printf("\n exchange tou rank 0: %d \n",send_bound[i]);
        }    
    }else if( rank == 1){
        for(int i=0;i<2;i++){
            printf("\n exchange tou rank 1: %d \n",send_bound[i]);
        }          
    }

    return (0);
}
// compare function
int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}



