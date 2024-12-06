#include "../minishell.h"

int	builtin_only(char **commands)
{
	if (commands[0] != NULL)
	{
		if (ft_strcmp(commands[0], "cd") == 0 || ft_strcmp(commands[0],
				"exit") == 0 || (ft_strcmp(commands[0], "export") == 0
				&& commands[1] != NULL) || (ft_strcmp(commands[0], "unset") == 0
				&& commands[1] != NULL))
			return (1);
	}
	return (0);
}

int is_nemuric(char *command)
{
    int i = 0;
    if(command[0] == '-')
        i++;
    while(command[i])
    {
        if(command[i] < '0' || command[i] > '9')
            return(0);
        i++;
    }
    return(1);
}

int there_dollar(char *command)
{
    int i = 0;
    while(command[i])
    {
        if(command[i] == '$')
            return(1);
        i++;
    }
    return(0);
}

void    expand_dollar(t_data data, char *command)
{
    int j = 0;

    while(command[j])
    {
        while(command[j] && command[j] != '$')
        {
            printf("%c", command[j]);
            j++;
        }
        if(command[j] == '$' && command[j + 1] == '?')
        {
            printf("%d", data.exit_status);
            j += 2;
        }
        else if(command[j] == '$' && command[j + 1] != '?')
        {
            while(command[j] && command[j] != ' ')
                j++;
        }
    }
}

void    get_status(char **commands)
{
    if(is_nemuric(commands[1]))
    {
        if(commands[1] && !commands[2])
        {
            if(ft_atoi(commands[1]) > 0)
            {
                printf("exit\n");
                exit(ft_atoi(commands[1]));
            }
            else
            {
                printf("exit\n");
                exit(256 + ft_atoi(commands[1]));
            }
        }
        else
            printf("minishell: exit\nexit: too many arguments\n");
    }
    else
    {
        printf("minishell: exit\nexit: %s: numeric argument required\n", commands[1]);
        exit(255);
    }
}
