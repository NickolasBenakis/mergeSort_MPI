#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
/*
     *  You can simply compile and run this script using:
     *  - mpicc main.c -o out && mpirun -np 4 out 24
     * */
// int main(int argc, char** argv){

//     int n = atoi(argv[1]); // dexomai arithmo stoixeiwn apo to command
//     int *original_array = malloc(n * sizeof(int)); // orizw ton pointer tou array
//     /*
//     The malloc() function reserves a block of memory of the specified number of bytes.
//     And, it returns a pointer of type void which can be casted into pointer of any form.
//     ** example of mallon : ptr = (cast-type*) malloc(byte-size)
//     */

//     for (int i = 0; i < n; i++) {
//         original_array[i] = rand() % (2 * n); // pernaw ta stoixeia tou array mesa
//     }

//     printf('to Array dexetai to %d\n',original_array);
//     printf("Hello world\n");
//     return(0);

// }

//Program with static array

int cmpfunc(const void *, const void *);

int main(int argc, const char *argv[])
{
    //int n = 16; //number of items
    int n = 8;
    //int original_array[n - 1];
    //int original_array[] = { 16, 13, 10, 8, 9 , 15, 14, 1, 4 , 3 , 5, 11, 7, 6 , 2, 12};
    int original_array[] = { 16, 13, 10, 8, 9 , 15, 1, 4 };
    //int *a = malloc(sizeof(int)*n);
    
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
    // if(rank == 0){
    //     min0 = sub_array[0];
    //     max0 = sub_array[num-1];
    //     printf("\nMin for rank %d, is %d ",rank,sub_array[0]);
    //     printf("\nMax for rank %d, is %d ",rank,sub_array[num-1]);

    // }
    // else if(rank == 1){
    //     min1 = sub_array[0];
    //     max1 = sub_array[num-1];
    //     printf("\nMin for rank %d, is %d ",rank,sub_array[0]);
    //     printf("\nMax for rank %d, is %d \n",rank,sub_array[num-1]);
    // }
    // deuteros tropos gia eschange boundaries betwween paired groups
    int boundary[] = { sub_array[0], sub_array[num-1]};
    // for (int i= 0; i<size;i++){
    //     printf(" hi %d \n",boundary[i]);
    // }
    min = sub_array[0];
    max = sub_array[num-1];

    
    if ( rank == 0 ){
        MPI_Send(&boundary,1,MPI_INT,1,msgtag, MPI_COMM_WORLD);
        MPI_Recv(&boundary,1,MPI_INT,1,msgtag,MPI_COMM_WORLD,&status);
        printf("Hello this is boundary min from rank 1 : %d\n",boundary[0]);
        printf("Hello this is boundary max from rank 1 : %d\n",boundary[1]);
    }else if ( rank == 1) {
        MPI_Send(&boundary,1,MPI_INT,0,msgtag, MPI_COMM_WORLD);
        MPI_Recv(&boundary,1,MPI_INT,0,msgtag,MPI_COMM_WORLD,&status);
        printf("Hello this is boundary min from rank 0 : %d\n",boundary[0]);
        printf("Hello this is boundary max from rank 0 : %d\n",boundary[1]);
    }

    // MPI_Bcast(&min,0,MPI_INT,1,MPI_COMM_WORLD);
    // MPI_Bcast(&max,0,MPI_INT,1,MPI_COMM_WORLD);

    if (num % 2 != 0){  // Elegxw an einai Artio i Peritto to plithos tou sub Array
        median_first= (sub_array[middle] + sub_array[middle+1])/2;
    }else{
        median_first = sub_array[middle];
    }

    // if( min0 < min1 ){
    //     /* AN to min tis listas tou rank 0 processor einai < tou min tou rank 1 
    //     tote i lista sto rank 0 tha kratisei tis lower times dld tis times katw tou median 
    //     kai meta paw stis times pou einai >= median 
    //     kai tis times anw i ises tou median tha tis stilei stin lista tis rank 1
    //     kai i rank 1 tha stilei tis times pou einai < = median stin lista tis rank 0
    //     */
        

    //     printf("\n Hello");
    //     for(int c=0;c<num;c++){
    //         if(sub_array[c] > median ){      // An stixio < median tote stilto ston allo processor

    //             MPI_Send(&sub_array[c],1,MPI_INT,1,tag,MPI_COMM_WORLD);
    //         }
    //     }
    
    // }else if( min0 > min1){
    //     printf("\nDAMN");
    // }
    
    return (0);
}
// compare function
int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}
