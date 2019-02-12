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
    int n = 16; //number of items
    int original_array[n - 1];
    // Step 1 : I set a list with n items
    printf("\nOriginal Array\n");
    for (int i = 0; i < n; i++)
    {
        original_array[i] = rand() % (2 * n);
        printf("%d, ", original_array[i]);
    }
    printf("\n");
    // Step 2 : I set MPI Communicator

    int rank, size, num, startTime, endTime, finalTime;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    num = n / size;
    int sub_array[num];

    MPI_Scatter(original_array, num, MPI_INT,
                sub_array, num, MPI_INT,
                0, MPI_COMM_WORLD);

    //qsort(original_array, n, sizeof(int), cmpfunc);
    qsort(sub_array, num, sizeof(int), cmpfunc);

    printf("\nSorted Array: \n");
    for (int i = 0; i < num; i++)
    {
        printf("%d, ", sub_array[i]);
    }
    printf("\n");

    return (0);
}
// callback function
int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}
