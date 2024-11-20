#include "minishell.h"

int  not_valid_unset(char **commands)
{
	int i = 1;
	int j = 1;
	while(commands[i])
	{
		j = 1;
		if((commands[i][0] < 'a' || commands[i][0] > 'z') && (commands[i][0] < 'A' || commands[i][0] > 'Z') && commands[i][0] != '_')
		{
			printf("unset: `%s': not a valid identifier\n", commands[i]);
			return(1);
		}
		while(commands[i][j])
		{
			if((commands[i][j] < 'a' || commands[i][j] > 'z') && (commands[i][j] < 'A' || commands[i][j] > 'Z') && (commands[i][j] < 'j' || commands[i][j] > '9') && commands[i][j] != '_')
			{
				printf("unset: `%s': not a valid identifier\n", commands[i]);
				return(1);
			}
			j++;	
		}
		i++;
	}
	return(0);
}

void    remove_from_env(t_data *data, char *key)
{
    t_env *tmp;
    t_env *env_lst = data->env_lst;
    while(env_lst && env_lst->next)
    {
        if(ft_strcmp(env_lst->next->key , key) == 0)
        {
            tmp = env_lst->next;
            env_lst = tmp->next;
            free(tmp);
            return ;
        }
        env_lst = env_lst->next;
    }
}

void    remove_from_export(t_data *data, char *key)
{
    t_env *tmp;
    t_env *export_lst = data->export_lst;
    while(export_lst->next)
    {
        if(ft_strcmp(export_lst->next->key , key) == 0)
        {
            tmp = export_lst->next;
            export_lst->next = tmp->next;
            free(tmp);
            return ; 
        }
        export_lst = export_lst->next;
    }
}

void    unset_commands(t_data *data, char **key)
{
    int i = 1;
    while(data->cmd_lst->commands[i])
    {
        remove_from_env(data, key[i]);
        remove_from_export(data, key[i]);
        i++;
    }
}