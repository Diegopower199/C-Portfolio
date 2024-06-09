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
    printf("introduce numero (anillo):");
    scanf("%d", &n);

    printf("El proceso %d ha enviado %d al proceso %d\n", myrank, n, next);
    MPI_Send(&n, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
  }

  do
  {

    MPI_Recv(&n, 1, MPI_INT, from, 0, MPI_COMM_WORLD, &status);
    printf("El proceso %d ha recibido %d\n", myrank, n);

    if (myrank == 0)
    {
      --n;
    }

    if (n > 0)
    {
      MPI_Send(&n, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
      printf("El proceso %d envia %d al proceso %d\n", myrank, n, next);
    }

  } while (n > 0);
  printf("Proceso %d termina\n", myrank);

  MPI_Finalize();
  return 0;
}
