#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#define MAXLON 1000

pthread_t thread1, thmain; // declaracion de los threads
pthread_attr_t attr;       // atributo de los threads
void *func1(void *arg);    // prototipo de funcion que ejecuta thread
void cuenta(char *nombre);
char *argumento;

void *func1(void *arg)
{
    printf("Thread ejecuta cuenta\n");
    cuenta(argumento);
    pthread_exit(NULL);
}

void cuenta(char *nombre)
{
    int pos, cont = 0, leidos;
    char cadena[MAXLON];
    int fd;
    fd = open(nombre, O_RDONLY);
    while ((leidos = read(fd, cadena, MAXLON)) != 0)
    {
        for (pos = 0; pos < leidos; pos++)
        {
            if ((cadena[pos] == 'a') || (cadena[pos] == 'A'))
            {
                cont++;
            }
        }
    }
    printf("Fichero %s: %d caracteres 'a' o 'A' encontrados\n", nombre, cont);
    close(fd);
}

int main(int argc, char *argv[])
{
    printf("aaa=%d\n", argc);
    if (argc != 2)
    {
        printf("Indica el nombre de un fichero.%s\n", argv[0]);
        exit(0);
    }
    argumento = argv[1];
    thmain = pthread_self();                      // Llama main thread
    pthread_create(&thread1, &attr, func1, NULL); // Crea parametros thread
    pthread_join(thread1, NULL);                  // main thread espera a que thread termine
    pthread_exit(NULL);                           // FIN
    return 0;
}
