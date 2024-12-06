#include "../minishell.h"

void    handle_pwd(t_data *data)
{
    char *pwd = get_pwd();
    if(pwd)
    {
        printf("%s\n", pwd);
        data->exit_status = 0;
    }
    else
        data->exit_status = 1;
}

void    handle_echo(t_data *data, char **commands)
{
    if(ft_strcmp(commands[0], "echo") == 0)
    {
        echo_printing(*data, commands);
        data->exit_status = 0;
    }
}

void handle_cd(t_data *data)
{
    update_old_pwd(data);
    change_dir(data);
    update_new_pwd(data);
}

void    handle_exit(char **commands)
{
    if(commands[1] == NULL)
    {
        printf("exit\n");
        exit(EXIT_SUCCESS);
    }
    else
        get_status(commands);
}
