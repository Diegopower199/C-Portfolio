#include <mpi.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int nproc;  // numero de procesos
    int myrank; // id del proceso

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    printf("Hola mundo, soy el proceso %d de un total de %d y tarda %f\n", myrank, nproc, MPI_Wtime());

    MPI_Finalize(); // finalizar.
}

double MPI_Wtime()
{
    double time = 0.0;

    MPI_Barrier(MPI_COMM_WORLD);
    clock_t start = clock();

    MPI_Barrier(MPI_COMM_WORLD);
    clock_t finish = clock();

    return (double)(time = finish - start) / CLOCKS_PER_SEC;
}
