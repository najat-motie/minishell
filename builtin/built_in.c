#include "../minishell.h"

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
    if(ft_strcmp(commands[0], "echo") == 0 && ft_strcmp(commands[1], "$?") == 0)
    {
        printf("%d\n", data->exit_status);
        data->exit_status = 0;
    }
    else if(ft_strcmp(commands[0], "echo") == 0)
    {
        echo_printing(commands);
        data->exit_status = 0;
    }
}

void handle_cd(t_data *data)
{
    update_old_pwd(data);
    change_dir(data);
    update_new_pwd(data);
}

void    handle_export(t_data *data, char **commands)
{
    if(not_valid_export(commands))
    {
        data->exit_status = 1;
        return ;
    }
    export_commands(data, commands);
    data->exit_status = 0;
}

void    handle_unset(t_data *data, char **commands)
{
    if(not_valid_unset(commands))
    {
        data->exit_status = 1;
        return ;
    }
    unset_commands(data, commands);
    data->exit_status = 0;
}
