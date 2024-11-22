#include "../minishell.h"

int  not_valid_export(char **commands)
{
	int i = 1;
	int j = 1;
	while(commands[i])
	{
		j = 1;
		if((commands[i][0] < 'a' || commands[i][0] > 'z') && (commands[i][0] < 'A' || commands[i][0] > 'Z') && commands[i][0] != '_')
		{
			printf("export: `%s': not a valid identifier\n", commands[i]);
			return(1);
		}
		while(commands[i][j])
		{
			if((commands[i][j] < 'a' || commands[i][j] > 'z') && (commands[i][j] < 'A' || commands[i][j] > 'Z') && (commands[i][j] < 'j' || commands[i][j] > '9') && commands[i][j] != '_' && commands[i][j] != '=')
			{
				printf("export: `%s': not a valid identifier\n", commands[i]);
				return(1);
			}
			j++;	
		}
		i++;
	}
	return(0);
}

void    fill_env_lst(t_data *data)
{
    int i = 0;
	char **key = get_keys(data->envp);
	char **value = get_value(data->envp);
	data->env_lst = NULL;
    while(data->envp[i])
    {
        add_back_env(&data->env_lst, ft_new_env(key[i], value[i], 1));
        i++;
    }
}

void	add_to_lst(t_data *data, char *key, char *value, int equal)
{
	t_env *envp_tmp = data->env_lst;
	while(envp_tmp)
	{
		if(ft_strcmp(envp_tmp->key, key) == 0)
		{
			free(envp_tmp->value);
			envp_tmp->value = value;
			return ;
		}
		else
			envp_tmp = envp_tmp->next;
	}
	add_back_env(&data->env_lst, ft_new_env(key, value, equal));
}

void	export_commands(t_data *data, char **commands)
{
	int i = 1;
	int equal = 0;
	char **var;
	char *key_cmd;
	char *value_cmd;
	while(commands[i])
	{
		if(there_equal(commands[i]))
			equal = 1;

		var = ft_split(commands[i], '=');
		key_cmd = var[0];
		value_cmd = var[1];
		add_to_lst(data, key_cmd, value_cmd, equal);
		i++;
	}
}