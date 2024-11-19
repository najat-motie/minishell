#include "minishell.h"

int is_builtin(char *command)
{
    if (command != NULL)
    {
        if(ft_strncmp(command, "cd", ft_strlen(command)) == 0 || ft_strncmp(command, "pwd", ft_strlen(command)) == 0 
            || ft_strncmp(command, "echo", ft_strlen(command)) == 0
            || ft_strncmp(command, "exit", ft_strlen(command)) == 0 || ft_strncmp(command, "env", ft_strlen(command)) == 0 
            || ft_strncmp(command, "export", ft_strlen(command)) == 0 || ft_strncmp(command, "unset", ft_strlen(command)
            ) == 0)
            return (1);
    }
    return (0);
}

void    handle_cd(t_data *data)
{
    if(data->cmd_lst->commands[1] != NULL)
    {
        if(chdir(data->cmd_lst->commands[1]) != 0)
        {
            perror("cd");
            data->exit_status = -1;
        }
        else
            data->exit_status = 0;
    }
    else
    {
        char *home = getenv("HOME");
        if(home == NULL)
            return ;
        if(chdir(home) != 0)
        {
            perror("cd");
            data->exit_status = -1;
        }
        else
            data->exit_status = 0;
    }
}

void    handle_pwd(t_data *data)
{
    char cwd[1024];
    if(getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
        data->exit_status = 0;
    }
    else
    {
        perror("pwd");
        data->exit_status = 1;
    }
}

void    handle_echo(t_data *data, char **commands)
{
    int i;
    int j;
    int newline;

    i = 1;
    newline = 1;
    if(commands[1] != NULL)
    {
        if(commands[1][0] == '-' && commands[1][1] == 'n')
        {
            i++;
            j = 1;
            while(commands[1][j] == 'n')
                j++;
            if(commands[1][j] == '\0')
                newline = 0;
            else
                i--;
        }
        while(commands[i] != NULL)
        {
            printf("%s", commands[i]);
            i++;
            if(commands[i])
                printf(" ");
        }
    }
    if(newline)
        printf("\n");
    data->exit_status = 0; 
}

void    echo(t_data *data, char **commands)
{
    if(ft_strcmp(commands[0], "echo") == 0 && ft_strcmp(commands[1], "$?") == 0)
    {
        printf("%d\n", data->exit_status);
        data->exit_status = 0;
    }
    else if(ft_strcmp(commands[0], "echo") == 0)
            handle_echo(data, commands);
}
void builtin_commands(t_data *data, char **commands)
{
    if (commands[0] != NULL)
    {
        if(ft_strcmp(commands[0], "echo") == 0)
            echo(data, commands);
        if(ft_strcmp(commands[0], "cd") == 0)
        {
            update_old_pwd(data);
            handle_cd(data);
            update_new_pwd(data);
        }
        if(ft_strcmp(commands[0], "pwd") == 0)
            handle_pwd(data);
        if(ft_strcmp(commands[0], "exit") == 0)
        {
            printf("exit\n");
            exit(EXIT_SUCCESS);
        }
        if(ft_strcmp(commands[0], "env") == 0)
        {
            print_env(*data);
            data->exit_status = 0;
        }
        if(ft_strcmp(commands[0], "export") == 0 && commands[1] == NULL)
        {
            print_export(*data);
            data->exit_status = 0;
        }
        else if(ft_strcmp(commands[0], "export") == 0 && commands[1] != NULL)
        {
            if(not_valid_export(commands))
            {
                data->exit_status = 1;
                return ;
            }
            export_commands(data);
            data->exit_status = 0;
        }
        if(ft_strcmp(commands[0], "unset") == 0 && commands[1] != NULL)
        {
            if(not_valid_unset(commands))
            {
                data->exit_status = 1;
                return ;
            }
            handle_unset(data, commands);
            data->exit_status = 0;
        }
    }
}
