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

void    fill_export_lst(t_data *data)
{
    int i = 0;
	char **key = get_keys(data->envp);
	char **value = get_value(data->envp);
	data->export_lst = NULL;
    while(data->envp[i])
    {
        add_back_env(&data->export_lst, ft_new_env(add_quoutes(key[i], value[i]), key[i], value[i]));
		if(ft_strcmp(key[i], "PWD") == 0)
			add_back_env(&data->export_lst, ft_new_env(ft_strdup("OLDPWD"), ft_strdup("OLDPWD"), NULL));
        i++;
    }
}

void	add_to_export_lst(t_data *data, char *key, char *value, char *command)
{
	t_env *export_tmp = data->export_lst;
	char *content;
	if(is_quouted(value))
		content = ft_strdup(command);
	else
		content = add_quoutes(key, value);
	while(export_tmp)
	{
		if(ft_strcmp(export_tmp->key, key) == 0)
		{
			free(export_tmp->value);
			export_tmp->value = ft_strdup(value);
			export_tmp->content = content;
			return ;
		}
		else
			export_tmp = export_tmp->next;
	}
	add_back_env(&data->export_lst, ft_new_env(content, key, ft_strdup(value)));
}

void	export_commands(t_data *data, char **commands)
{
	int i = 1;
	char **var;
	char *key_cmd;
	char *value_cmd;
	while(commands[i])
	{
		var = ft_split(commands[i], '=');
		key_cmd = var[0];
		value_cmd = ft_strchr(commands[i], '=');
		if(value_cmd)
		{
			add_to_env_lst(data, key_cmd, value_cmd, commands[i]);
			add_to_export_lst(data, key_cmd, value_cmd, commands[i]);
		}
		else
			add_to_export_lst(data, key_cmd, value_cmd, commands[i]);
		i++;
	}
}
