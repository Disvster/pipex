#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// int main()
// {
//     pid_t pid;
//
//     pid = fork();
//     if (pid == -1)
//     {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }
//
//     if (pid == 0)
//         printf("This is the child process. (pid: %d)\n", getpid());
//     else
//         printf("This is the parent process. (pid: %d)\n", getpid());
//     return (0);
// }

int main()
{
    int fd[2];
    pid_t pid;
    char buffer[13];

    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        close(fd[0]); // close the read end of the pipe
        write(fd[1], "Hello parent!", 13);
        close(fd[1]); // close the write end of the pipe
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(fd[1]); // close the write end of the pipe
        read(fd[0], buffer, 13);
        close(fd[0]); // close the read end of the pipe
        printf("Message from child: '%s'\n", buffer);
        exit(EXIT_SUCCESS);
    }
}

// int main()
// {
//     if (unlink("test.txt") == 0)
//         printf("File successfully deleted");
//     else
//         printf("Error deleting file");
//
//     return (0);
// }
