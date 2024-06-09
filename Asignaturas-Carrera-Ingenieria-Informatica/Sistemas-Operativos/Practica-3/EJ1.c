
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define SIZE 512

int main(int argc, char **argv)
{
  pid_t pid;
  int p[2], p2[2], readbytes; // solo un pipe porque solo genera el hijo y consume el padre
  char buffer[SIZE];

  pipe(p);
  pipe(p2);

  if ((pid = fork()) == 0)
  { // Hijo

    close(p[0]);  // cerramos el lado de lectura del pipe
    close(p2[1]); // cerramos el lado de escribir del pipe

    while ((readbytes = read(p2[0], buffer, SIZE)) > 0)
    {
      write(1, buffer, readbytes);
    }
    close(p2[0]);

    strcpy(buffer, "Hijo escribe\n");
    write(p[1], buffer, strlen(buffer));
    close(p[1]);
  }
  else
  { // Padre recibe el nodo

    close(p[1]);  // cerramos el lado de escribir del pipe
    close(p2[0]); // cerramos el lado de leer del pipe

    strcpy(buffer, "Padre lee\n");
    write(p2[1], buffer, strlen(buffer));
    close(p2[1]);

    while ((readbytes = read(p[0], buffer, SIZE)) > 0)
    { // padre consumiendo datos
      write(1, buffer, readbytes);
    }
    close(p[0]);
  }
  waitpid(pid, NULL, 0);
  exit(0);
}
