#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int pipes[2], fp;
    time_t ini = time(NULL), fin;
    // create a descriptor for the pipe to read a file.txt
    pipe(pipes);

    FILE *file_1 = argv[2];
    FILE *file_2 = argv[3];

    if (fork() == 0)
    {
        if (fork() == 0)
        {
            // child process
            // close the reading end of the pipe
            close(pipes[0]);
            // redirect the standard output to the writing end of the pipe
            dup2(pipes[1], STDOUT_FILENO);
            // execute the command
            execlp("grep", "grep", argv[1], file_1, NULL);
            // close the writing end of the pipe
            close(pipes[1]);
        }
        else
        {
            if (fork() == 0)
            {
                // child process
                // close the reading end of the pipe
                close(pipes[0]);
                // redirect the standard output to the writing end of the pipe
                dup2(pipes[1], STDOUT_FILENO);
                // execute the command
                execlp("grep", "grep", argv[1], file_2, NULL);
                // close the writing end of the pipe
                close(pipes[1]);
            }
            else
            {
                close(pipes[1]);

                fp = creat(argv[4], 00644);

                dup2(fp, STDOUT_FILENO);
                execlp("wc", "wc", "-l", NULL);

                close(pipes[0]);
                close(fp);
            }
        }
    }

    return 0;
}
