#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
#include <string.h>

int main(argc, argv)
int argc;
{
    int rank;
    char msg[20];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        strcpy(msg, "Hola mundo");
    }

    MPI_Bcast(&msg, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Soy el proceso %d y he recibido el dato %s\n", rank, msg);

    MPI_Finalize();

    return 0;
}
