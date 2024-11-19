#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

// int main() 
// {
//     char *commands[] = { "ls", NULL, NULL };    
//     // char *envp[] = { NULL };                    // Environment variables
//     // char *path = get_path("ls");
//     // ft_printf("-->%s\n", path);
//     execve("/bin/ls", commands, NULL);               // Replaces the current process with ls
//     ft_printf("hhhh\n");
//     return 0;                                    // This line is never reached unless execve fails
// }

// int main(int argc, char *commands[], char *envp[]) {
//     // Print each environment variable
//     for (int i = 0; envp[i] != NULL; i++) {
//         printf("%s\n", envp[i]);
//     }
//     return 0;
// }

// char *func(char *s)
// {
//     char *var = getenv("HOME");
//     printf("var %p\n", var);
//     return(var);
// }
// int main()
// {
//     char *var = "hi";
//     char *s = func(var);
//     printf("s %p\n", s);
//     // printf("%s\n", s);
//     // if(var == NULL)
//     //     return(1);
// }
