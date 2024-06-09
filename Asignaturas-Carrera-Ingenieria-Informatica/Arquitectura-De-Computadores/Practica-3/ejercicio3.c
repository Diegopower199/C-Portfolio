#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
    int size, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int arr[size], recep1[size], recep2[size];

    for (int pos = 0; pos < size; pos++)
    {
        arr[pos] = rank + 1;
    }

    MPI_Reduce(&arr, &recep1, size, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&arr, &recep2, size, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("Suma:");
        for (int pos = 0; pos < size; pos++)
        {
            printf(" %d ", recep1[pos]);
        }
        printf("\n");

        printf("Producto:");
        for (int pos = 0; pos < size; pos++)
        {
            printf(" %d ", recep2[pos]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
