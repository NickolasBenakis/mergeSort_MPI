#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
     *  You can simply compile and run this script using:
     *  - mpicc main.c -o out && mpirun -np 4 out 24
     * */

//order of holding keys
int getOrder(int myBoundaries[2], int hisBoundaries[2], int myRank, int hisRank)
{
    int myMin = myBoundaries[0];
    int myMax = myBoundaries[1];
    int hisMin = hisBoundaries[0];
    int hisMax = hisBoundaries[1];

    if (myMin < hisMin)
    {
        return -1;
    }
    if (myMin > hisMin)
    {
        return 1;
    }
    if (myMax > hisMax)
    {
        return 1;
    }
    if (myMax < hisMax)
    {
        return -1;
    }
    if (myMin == hisMin && myMax == hisMax)
    {

        if (myRank == hisRank)
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

int cmpfunc(const void *, const void *);

int main(int argc, const char *argv[])
{
    int n = 8;
    int original_array[] = {16, 13, 10, 8, 9, 15, 2, 4};
    int rank, size, num, startTime, endTime, finalTime, tag;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;
    
    // Step 1 : I set a list with n items
    if (rank == 0)
    {
        printf("\nOriginal Array\n");
        for (int i = 0; i < n; i++)
        {
            //original_array[i] = rand() % (2 * n);
            if (i == n - 1)
            {
                printf("%d", original_array[i]);
            }
            else
            {
                printf("%d, ", original_array[i]);
            }
        }
        printf("\n");
    }

    num = n / size;
    int sub_array[num], first, last, middle, splitter, median, median_first, search, min0, max0, min1, max1, min, max, msgtag;

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
    int my_bound[] = {sub_array[0], sub_array[num - 1]};   // ayta tha exw local
    int send_bound[] = {sub_array[0], sub_array[num - 1]}; // ayta tha steilw
    if (rank == 0)
    {
        for (int i = 0; i < 2; i++)
        {
            //  printf("\n boundaries tou rank 0 : %d \n", my_bound[i]);
        }
    }
    else if (rank == 1)
    {
        for (int i = 0; i < 2; i++)
        {
            //  printf("\n boundaries tou rank 1 : %d \n", my_bound[i]);
        }
    }

    if (rank == 0)
    {
        for (int i = 0; i < 2; i++)
        {
            //   printf("\n Prin exchange tou rank 0: %d \n", send_bound[i]);
        }

        MPI_Send(&send_bound, 2, MPI_INT, 1, msgtag, MPI_COMM_WORLD);
        MPI_Recv(&send_bound, 2, MPI_INT, 1, msgtag, MPI_COMM_WORLD, &status);

        for (int i = 0; i < 2; i++)
        {
            //  printf("\n Meta exchange tou rank 0: %d \n", send_bound[i]);
        }
    }
    else if (rank == 1)
    {
        for (int i = 0; i < 2; i++)
        {
            //  printf("\n Prin exchange tou rank 1: %d \n", send_bound[i]);
        }

        MPI_Send(&send_bound, 2, MPI_INT, 0, msgtag, MPI_COMM_WORLD);
        MPI_Recv(&send_bound, 2, MPI_INT, 0, msgtag, MPI_COMM_WORLD, &status);

        for (int i = 0; i < 2; i++)
        {
            // printf("\n Meta exchange tou rank 1: %d \n", send_bound[i]);
        }
    }
    // Vriskw intervals
    int int_counter;
    int *intervals = malloc(int_counter * sizeof(int));
    for (int i = 0; i < num; i++)
    {
        if (sub_array[i] > send_bound[0] && sub_array[i] < send_bound[1])
        {
            intervals[int_counter] = sub_array[i];
            int_counter++;
        }
    }

    if (rank == 0)
    {
        printf("\noveralp counter tou 0 : %d", int_counter);

        for (int i = 0; i < int_counter; i++)
        {
            printf("\noveralp tou rank 0 : %d", intervals[i]);
        }
    }
    else if (rank == 1)
    {
        printf("\noveralp counter tou 1 : %d", int_counter);

        for (int i = 0; i < int_counter; i++)
        {
            printf("\noveralp tou rank 1 : %d", intervals[i]);
        }
    }

    if (rank == 0)
    {
        if (int_counter % 2 == 0)
        { //perittos
            median = intervals[int_counter / 2 + 1];
        }
        else
        { // artios
            int middle = round(int_counter / 2);
            median = intervals[middle];
        }
        printf("\no Median einai : %d kai ton vrika stin Rank 0 \n", median);
        MPI_Send(&median, 1, MPI_INT, 1, msgtag, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Recv(&median, 1, MPI_INT, 0, msgtag, MPI_COMM_WORLD, &status);
        printf("\neimai i Rank 1 kai pira to median %d\n", median);
    }
    int tr_counter_to0;
    int tr_counter_to1;

    int *transfer_to0 = malloc(tr_counter_to0 * sizeof(int));
    int *transfer_to1 = malloc(tr_counter_to1 * sizeof(int));

    if (rank == 0)

    {
        for (int i = 0; i < int_counter; i++)
        {
            if (intervals[i] <= median)
            {
                transfer_to1[tr_counter_to1] = intervals[i];
                tr_counter_to1++;
            }
        }
        MPI_Send(&tr_counter_to1, 1, MPI_INT, 1, msgtag, MPI_COMM_WORLD);
        MPI_Recv(&tr_counter_to0, 1, MPI_INT, 1, msgtag, MPI_COMM_WORLD, &status);
        for (int i = 0; i < tr_counter_to1; i++)
        {
            MPI_Send(&transfer_to1[i], 1, MPI_INT, 1, msgtag, MPI_COMM_WORLD);
        }
        for (int i = 0; i < tr_counter_to0; i++)
        {
            MPI_Recv(&transfer_to0[i], 1, MPI_INT, 1, msgtag, MPI_COMM_WORLD, &status);
        }
        printf("\nTransfer counter stin rank 1 : %d \n", tr_counter_to1);
        for (int i = 0; i < tr_counter_to0; i++)
        {
            printf("Eimai Rank 0 kai exw parei ta Stoixeia : %d apo tin Rank 1 \n", transfer_to0[i]);
        }

        // merge Overlaps with sub_array and make a new List in each processor
        int num2=0;
        int *final_subarray = malloc(num2 * sizeof(int));
        for (int i = 0; i < num; i++)
        {
            if (sub_array[i] > median)
            {
                final_subarray[num2] = sub_array[i];
                num2++;
            }
        }
        int num3 = 0;
        for (int i = 0; i < tr_counter_to0; i++)
        {
            final_subarray[num2+i] = transfer_to0[i];
            num3++;
        }
        int sumNum = num2+num3;
        qsort(final_subarray, sumNum, sizeof(int), cmpfunc);

        for (int i = 0; i < sumNum; i++)
        {
            printf(" FINAL RANK 0 : %d \n", final_subarray[i]);
        }
    }
    else if (rank == 1)
    {
        for (int i = 0; i < int_counter; i++)
        {
            if (intervals[i] >= median)
            {
                transfer_to0[tr_counter_to0] = intervals[i];
                tr_counter_to0++;
            }
        }
        MPI_Send(&tr_counter_to0, 1, MPI_INT, 0, msgtag, MPI_COMM_WORLD);
        MPI_Recv(&tr_counter_to1, 1, MPI_INT, 0, msgtag, MPI_COMM_WORLD, &status);
        for (int i = 0; i < tr_counter_to0; i++)
        {
            MPI_Send(&transfer_to0[i], 1, MPI_INT, 0, msgtag, MPI_COMM_WORLD);
        }
        for (int i = 0; i < tr_counter_to1; i++)
        {
            MPI_Recv(&transfer_to1[i], 1, MPI_INT, 0, msgtag, MPI_COMM_WORLD, &status);
        }
        printf("\nTransfer counter stin rank 0 : %d \n", tr_counter_to0);
        printf("\nPira apo tin rank 0 to : %d \n", transfer_to1[1]);

        for (int i = 0; i < tr_counter_to1; i++)
        {
            printf("Eimai Rank 1 kai exw parei ta Stoixeia : %d apo tin Rank 0 \n", transfer_to1[i]);
        }

        // for (int i = 0; i < tr_counter_to1; i++)
        // {
        //     send_bound[2 + i] = transfer_to1[i];
        // }

        // for (int i = 0; i < 2 + tr_counter_to1; i++)
        // {
        //     printf(" FINAL RANK 1 : %d \n", send_bound[i]);
        // }

        //

        int num2=0;
        int *final_subarray = malloc(num2 * sizeof(int));
        for (int i = 0; i < num; i++)
        {
            if (sub_array[i] < median)
            {
                final_subarray[num2] = sub_array[i];
                num2++;
            }
        }
        int num3 = 0;
        for (int i = 0; i < tr_counter_to1; i++)
        {
            final_subarray[num2+i] = transfer_to1[i];
            num3++;
        }
        int sumNum = num2+num3;
        qsort(final_subarray, sumNum, sizeof(int), cmpfunc);

        for (int i = 0; i < sumNum; i++)
        {
            printf(" FINAL RANK 1 : %d \n", final_subarray[i]);
        }
    }

    return (0);
}
// compare function
int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}
