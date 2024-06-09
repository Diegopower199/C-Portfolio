#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
  MPI_Status status;
  int n, myrank, nproc, next, from;

  MPI_Init(&argc, &argv); // inicializamos
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);

  next = (myrank + 1) % nproc;         // envio al siguiente nodo
  from = (myrank + nproc - 1) % nproc; // nodo del que proviene

  if (myrank == 0)
  {
    printf("introduce numero: ");
    scanf("%d", &n);
    MPI_Send(&n, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
    printf("Proceso %d envia %d al proceso %d\n", myrank, n, next);
  }
  else
  {
    MPI_Recv(&n, 1, MPI_INT, from, 0, MPI_COMM_WORLD, &status);

    if (myrank != n)
    {
      printf("Proceso %d envia %d al proceso %d\n", myrank, n, next);
      MPI_Send(&n, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
      printf("Proceso %d termina\n", myrank);
    }
    else
    {
      printf("Proceso %d termina\n", myrank);
    }
  }
  MPI_Recv(&n, 1, MPI_INT, from, 0, MPI_COMM_WORLD, &status);
  printf("Proceso %d termina\n", myrank);
  MPI_Finalize();
}
