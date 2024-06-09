#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
    int size, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int arr[size], recep1[size];

    for (int pos = 0; pos < size; pos++)
    {
        arr[pos] = rank + 1;
    }

    MPI_Reduce(&arr, &recep1, size, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("Suma:");
        for (int pos = 0; pos < size; pos++)
        {
            printf(" %d ", recep1[pos]);
        }
        printf("\n\n");
    }

    MPI_Alltoall(&arr, 1, MPI_INT, recep1, 1, MPI_INT, MPI_COMM_WORLD);

    if (rank == 0)
    {

        for (int i = 0; i < size; i++)
        {
            printf("Values collected on process (ALLTOALL) %d: ", rank + i);
            printf("%d,", recep1[i]);
            printf("\n");
        }
        printf("\n");
    }

    MPI_Allgather(&arr, 1, MPI_INT, recep1, 1, MPI_INT, MPI_COMM_WORLD);

    if (rank == 0)
    {

        for (int i = 0; i < size; i++)
        {
            printf("Values collected on process (ALLGATHER) %d: ", rank + i);
            for (int j = 0; j < size; j++)
            {
                printf("%d,", recep1[j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}