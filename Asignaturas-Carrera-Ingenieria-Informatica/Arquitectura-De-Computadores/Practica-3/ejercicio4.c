#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char **argv)
{
    int rank, size;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int resultado = 1;
    int rango = rank + 1;
    MPI_Reduce(&rango, &resultado, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("Soy el proceso %d y el factorial de %d es %d\n", rank, size, resultado);
    }

    MPI_Finalize();
    return 0;
}
