#include "../minishell.h"

void    change_dir(t_data *data)
{
    char *home;

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
        home = getenv("HOME");
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

void    print_env(t_data *data)
{
    t_env *tmp_lst = data->env_lst;
	while(tmp_lst)
	{
		printf("%s", tmp_lst->key);
        if(tmp_lst->value)
		    printf("=%s\n", tmp_lst->value);
        else
            printf("\n");
		tmp_lst = tmp_lst->next;
    }
    data->exit_status = 0;
}

void    print_export(t_data *data)
{
   t_env *tmp_lst = data->env_lst;
	while(tmp_lst)
	{
		printf("declare -x ");
		printf("%s", tmp_lst->key);
        if(tmp_lst->equal)
        {
            printf("=");
            printf("\"");
            if(tmp_lst->value != NULL)
                printf("%s", tmp_lst->value);
            printf("\"");
        }
        printf("\n");
        tmp_lst = tmp_lst->next;
    }
    data->exit_status = 0;
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