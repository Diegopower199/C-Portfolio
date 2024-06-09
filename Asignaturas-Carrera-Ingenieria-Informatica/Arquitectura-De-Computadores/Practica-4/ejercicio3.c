#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"
#include <math.h>

int main(int argc, char *argv[])
{
	int size, rank;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int numeroAleatorio = 0;
	int numeros[size];

	srand(getpid());
	numeroAleatorio = rand() % 2;

	int resultado = 0;
	int multiplicador = 1;

	MPI_Allgather(&numeroAleatorio, 1, MPI_INT, numeros, 1, MPI_INT, MPI_COMM_WORLD);
	// El primer parametro es que envia un numero, el segundo parametro es cuanto es el tamaÃ±o que envias, el cuarto parametro es donde lo recibe y solo recibe uno

	printf("Proceso %d , dato: %d\n", rank, numeroAleatorio);

	if (numeroAleatorio == 1)
	{

		if (rank == (size - 1))
		{
			multiplicador = 1;
		}
		else
		{
			multiplicador = (int)(pow(2, ((int)(size - rank - 1))));
		}
	}
	else
	{
		multiplicador = 0;
	}

	MPI_Reduce(&multiplicador, &resultado, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		printf("Numeros binarios: ");
		for (int pos = 0; pos < size; pos++)
		{
			printf("%d", numeros[pos]);
		}
		printf("\nSoy el proceso 0 y el numero decimal es: %d\n", resultado);
	}

	MPI_Finalize();
}
