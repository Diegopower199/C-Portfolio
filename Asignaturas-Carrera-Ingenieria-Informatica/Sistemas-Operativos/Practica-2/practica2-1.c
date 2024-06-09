#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t thread1, thread2, thmain; // declaracion de los threads
pthread_attr_t attr;                // atributo de los threads
int factorial(int fact);
void *func1(void *arg); // prototipo de las funciones que ejecutan los threads
void *func2(void *arg);
int one, two;

void *func1(void *arg)
{ // thread 1
    printf("Thread 1\n");
    int x = factorial(one);
    printf("Factorial de %d es %d\n\n", one, x);
    pthread_exit(NULL);
}

void *func2(void *arg)
{ // thread 2
    printf("Thread 2\n");
    int x = factorial(two);
    printf("Factorial de %d es %d\n\n", two, x);
    pthread_exit(NULL);
}

int factorial(int fact)
{ // calcula factorial
    int sum = 1;
    if (fact < 0)
    {
        return -1; // En caso de error
    }
    else
    {
        for (int i = 1; i <= fact; ++i)
        {
            sum *= i;
        }
    }
    return sum;
}

int main(int argc, char *argv[])
{
    one = atoi(argv[1]); // Convierto strings de argv a enteros con atoi
    two = atoi(argv[2]);
    thmain = pthread_self();                      // Llamamos al main thread
    pthread_create(&thread1, &attr, func1, NULL); // Inicializa los parametro de los threads por defecto
    pthread_create(&thread2, &attr, func2, NULL);
    pthread_join(thread1, NULL); // Main thread espera a que los otros threads terminen
    pthread_join(thread2, NULL);
    printf("Threads lanzados---FIN\n");
    pthread_exit(NULL); // FIN
    return 0;
}
