#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{

    int file = open("ficheroEjercicio1SO.txt", O_RDONLY | O_CREAT, 0644);

    if (file == -1)
    {
        perror("Error al abrir el fichero");
        exit(1);
    }

    int tamanoFichero = lseek(file, 0, SEEK_END);

    char *restoDeCaracteres = (char *)malloc(tamanoFichero * sizeof(char));
    lseek(file, 50, SEEK_SET);
    read(file, restoDeCaracteres, tamanoFichero);
    printf("Desde la posicion 50 hasta el final del fichero esta la siguiente informacion: %s\n", restoDeCaracteres);

    close(file);
    return 0;
}
