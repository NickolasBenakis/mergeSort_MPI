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

    // with static array
int main(int argc, const char * argv[]){
    int n = 16; // dexomai arithmo stoixeiwn apo to command
    int original_array[n-1];
    for (int i = 0; i < n; i++) {
        original_array[i] = rand() % (2 * n); // pernaw ta stoixeia tou array mesa
        //printf("original_array[%d] = %d\n",i,original_array[i]);
        printf(" This is the Address: %p, this the value : %d\n",&original_array,original_array[i]);
    }

    return(0);

}


