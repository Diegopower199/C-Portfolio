#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Error: debe ingresar el nombre de un directorio como parámetro.\n");
        return 1;
    }

    DIR *directorio = opendir(argv[1]);
    if (directorio == NULL)
    {
        printf("Error: no se puede abrir el directorio '%s'.\n", argv[1]);
        return 1;
    }

    struct dirent *archivo;
    struct stat atributos;
    int suma = 0; // Creamos una variable para guardar la suma de los tamaños de los archivos
    while ((archivo = readdir(directorio)) != NULL)
    {                                  // Recorremos todos los archivos del directorio
        char ruta[1000];               // Creamos una variable para guardar la ruta del archivo
        strcpy(ruta, argv[1]);         // Copiamos el nombre del directorio a la variable ruta
        strcat(ruta, "/");             // Agregamos una barra al final de la ruta
        strcat(ruta, archivo->d_name); // Agregamos el nombre del archivo al final de la ruta
        stat(ruta, &atributos);        // Obtenemos los atributos del archivo
        suma += atributos.st_size;     // Sumamos el tamaño del archivo a la suma
    }

    printf("La suma de los tamaños de los archivos en bytes es: %d\n", suma);

    closedir(directorio); // Cerramos el directorio
}
