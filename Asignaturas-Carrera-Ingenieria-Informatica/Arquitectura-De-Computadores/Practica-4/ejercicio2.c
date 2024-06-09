#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <math.h>

int main(int argc, char **argv)
{
    int envio[4], recep1[4];
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 4)
    {
        printf("El numero de procesos debe ser 4 para construir la matriz\n");
        return 0;
    }

    for (int i = 0; i <= size; i++)
    {
        envio[i] = (i + 1) + rank * size;
    }

    printf("%d %d %d %d\n", envio[0], envio[1], envio[2], envio[3]);

    MPI_Alltoall(&envio, 1, MPI_INT, &recep1, 1, MPI_INT, MPI_COMM_WORLD);

    printf("Proceso: %d : %d %d %d %d\n", rank, recep1[0], recep1[1], recep1[2], recep1[3]);

    MPI_Finalize();
    return 0;
}