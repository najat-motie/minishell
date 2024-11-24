#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
    char *args[] = {"ls", NULL};
    execve("ls", args, NULL);
    perror("execve");
    exit(EXIT_FAILURE);

    // if(access("ls", X_OK) == -1)
    //     perror("access");
}