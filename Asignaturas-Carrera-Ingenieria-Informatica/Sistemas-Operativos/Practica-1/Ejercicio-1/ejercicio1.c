#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int fd, bytes_escritos;
	char buffer[500];
	mode_t modo = S_IRWXU;

	FILE *archivo;

	archivo = fopen("./ejemplo", "r");

	strcpy(buffer, "./ejemplo");
	if ((fd = open("./ejemplo", O_RDWR)) == -1)
	{
		perror("Error al abrir o crear el fichero");
	}

	bytes_escritos = read(fd, buffer, 500);
	printf(buffer, 500);

	fclose(archivo);

	exit(0);
}
