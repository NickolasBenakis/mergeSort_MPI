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
    int sub_array[num], first, last, middle, splitter, median, search, min0,max0,min1,max1;

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
    if(rank == 0){
        min0 = sub_array[0];
        max0 = sub_array[num-1];
        printf("\nMin for rank %d, is %d ",rank,sub_array[0]);
        printf("\nMax for rank %d, is %d ",rank,sub_array[num-1]);

    }
    else if(rank == 1){
        min1 = sub_array[0];
        max1 = sub_array[num-1];
        printf("\nMin for rank %d, is %d ",rank,sub_array[0]);
        printf("\nMax for rank %d, is %d \n",rank,sub_array[num-1]);
    }


    if( min0 < min1 ){

        int middle = num/size;
        median = (sub_array[middle] + sub_array[middle+1])/2;
        for(int c=0;c<num;c++){
            if(sub_array[c]< median ){      // An stixio < median tote stilto ston allo processor

                MPI_Send(&sub_array[c],1,MPI_INT,1,tag,MPI_COMM_WORLD);
            }
        }
    
    }
    
    for ( int i = 0; i< num; i++){
        

    }

    // Step 3 : Search for overlapped intervals and exchange data
    first = 0;
    last = n - 1;
    // median = (sub_array[last]+sub_array[first])/2;
    // int *p = &median;
    //printf(" median %d\n",*p);
    middle = (first+last)/2;


    // while (first <= last) {
    //     if (array[middle] < search)
    //     first = middle + 1;    
    //     else if (array[middle] == search) {
    //         printf("%d found at location %d.\n", search, middle+1);
    //         break;
    //     }
    //     else
    //         last = middle - 1;

    //     middle = (first + last)/2;
    // }
    return (0);
}
// compare function
int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}
