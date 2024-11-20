#include "../minishell.h"

void handle_builtins(t_data *data, char **commands)
{
    if (commands[0] != NULL)
    {
        if(ft_strcmp(commands[0], "cd") == 0)
            handle_cd(data);
        if(ft_strcmp(commands[0], "exit") == 0)
        {
            printf("exit\n");
            exit(EXIT_SUCCESS);
        }
        if(ft_strcmp(commands[0], "export") == 0 && commands[1] != NULL)
            handle_export(data, commands);
        if(ft_strcmp(commands[0], "unset") == 0 && commands[1] != NULL)
            handle_unset(data, commands);
        if(ft_strcmp(commands[0], "echo") == 0)
            handle_echo(data, commands);
        if(ft_strcmp(commands[0], "pwd") == 0)
            handle_pwd(data);
        if(ft_strcmp(commands[0], "env") == 0 && commands[1] == NULL)
            print_env(data);
        if(ft_strcmp(commands[0], "export") == 0 && commands[1] == NULL)
            print_export(data);
    }
}
