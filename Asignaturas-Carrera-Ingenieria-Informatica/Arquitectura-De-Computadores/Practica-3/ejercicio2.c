#include <mpi.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
	int rank, value, size;
	int suma = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int indices[size];

	if (rank == 0)
	{
		for (int pos = 0; pos < size; pos++)
		{
			indices[pos] = pos;
		}
	}

	int valor = 0;
	MPI_Scatter(indices, 1, MPI_INT, &valor, 1, MPI_INT, 0, MPI_COMM_WORLD);

	suma = (valor + rank);

	// Gather -> enviarle al proceso 0 toda la informacion
	MPI_Gather(&suma, 1, MPI_INT, &indices, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		for (int pos = 0; pos < size; pos++)
		{
			printf("Valor = %d\n", indices[pos]);
		}
	}

	MPI_Finalize();

	return 0;
}
