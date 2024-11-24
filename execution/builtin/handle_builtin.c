#include "../../minishell.h"

int is_builtin(char *command)
{
    if (command != NULL)
    {
        if(ft_strcmp(command, "cd") == 0 || ft_strcmp(command, "pwd") == 0 || ft_strcmp(command, "echo") == 0 || ft_strcmp(command, "exit") == 0 || ft_strcmp(command, "env") == 0 || ft_strcmp(command, "export") == 0 || ft_strcmp(command, "unset") == 0)
            return (1);
    }
    return (0);
}

int builtin_only(char **commands)
{
    if(commands[0] != NULL)
    {
     if(ft_strcmp(commands[0], "cd") == 0 || ft_strcmp(commands[0], "exit") == 0 || (ft_strcmp(commands[0], "export") == 0 && commands[1] != NULL) || (ft_strcmp(commands[0], "unset") == 0 && commands[1] != NULL))
            return (1);
    }
    return(0);
}

void handle_builtins(t_data *data, char **commands)
{
    if (commands[0] != NULL)
    {
        if(ft_strcmp(commands[0], "exit") == 0)
            handle_exit();
        if(ft_strcmp(commands[0], "cd") == 0)
            handle_cd(data);
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
