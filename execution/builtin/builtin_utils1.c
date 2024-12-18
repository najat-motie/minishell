#include "../../minishell.h"

char *get_pwd()
{
    char cwd[1024];

    if(getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd");
        return(NULL);
    }
    return(ft_strdup(cwd));
}

void    change_to_home(t_data *data)
{
    char *home = retreive_value(*data, "HOME");
    if(home == NULL)
    {
        printf("minishell: cd: HOME not set\n");
        data->exit_status = 1;
    }
    else if(chdir(home) != 0)
    {
        perror("chdir");
        data->exit_status = 1;
    }
    else
        data->exit_status = 0;
}

void    change_dir(t_data *data)
{

    if(data->cmd_lst->commands[1] != NULL)
    {
        if(chdir(data->cmd_lst->commands[1]) != 0)
        {
            perror("chdir");
            data->exit_status = 1;
        }
        else
            data->exit_status = 0;
    }
    else
        change_to_home(data);
}

void    print_args(char **commands, int i)
{
    while(commands[i] != NULL)
    {

            printf("%s", commands[i]);
        i++;
        if(commands[i])
            printf(" ");
    }
}

void    echo_printing(char **commands)
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
        print_args(commands, i);
    }
    if(newline)
        printf("\n");
}