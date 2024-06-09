#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
int array2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
int square(int number);
void printArray(int array[]);

int square(int number)
{ // funcion para hacer el cuadrado del numero
    return number * number;
}

void printArray(int array[])
{ // funcion que imprime el array con un for
    for (int i = 0; i < 20; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n\n");
}

int main(void)
{

    pid_t childpid1, childpid2, childdead;

    childpid1 = fork();

    if (childpid1 == -1)
    {
        perror("fork mo pudo crear un hijo");
        exit(1);
    }
    else if (childpid1 == 0)
    {

        for (int i = 0; i < 20; i++)
        {
            if (array[i] % 2 == 1)
            {
                array[i] = square(array[i]);
            }
        }
        printf("impares:\n");
        printArray(array);
    }
    else
    {
        printf("soy el padre ,PID %d, y voy a esperar a mi hijo(PID %d)\n", getpid(), childpid1);

        if ((childdead = wait(0)) == -1)
        {
            perror("no he podido esperar");
        }
        else
        {
            printf("mi hijo con pid %d, ha muerto\n", childdead);
        }
    }

    childpid2 = fork();

    if (childpid2 == -1)
    {
        perror("fork mo pudo crear un hijo");
        exit(1);
    }
    else if (childpid2 == 0)
    {
        for (int i = 0; i < 20; i++)
        {
            if (array2[i] % 2 == 0)
            {
                array2[i] = square(array2[i]);
            }
        }
        printf("pares:\n");
        printArray(array2);
    }
    else
    {
        printf("soy el padre ,PID %d, y voy a esperar a mi hijo(PID %d)\n", getpid(), childpid2);

        if ((childdead = wait(0)) == -1)
        {
            perror("no he podido esperar");
        }
        else
        {
            printf("mi hijo con pid %d, ha muerto\n", childdead);
        }
    }

    exit(0);
}
