#include "minishell.h"

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

char *add_quoutes(char *command)
{
	char *cmnd = malloc(ft_strlen(command) + 3);
	if(cmnd == NULL)
		return(NULL);
	int i = 0;
	while(command[i] && command[i] != '=')
	{
		cmnd[i] = command[i];
		i++;
	}
	if(command[i] == '=')
	{
		cmnd[i++] = '=';
		int j = i;
		cmnd[i++] = '"';
		if(command[j] != '\0')
		{
			while(command[j])
			{
				cmnd[i] = command[j];
				i++;
				j++;
			}
		}
		cmnd[i++] = '"';
	}
	cmnd[i] = '\0';
	return(cmnd);
}

void    fill_export_lst(t_data *data)
{
    int i = 0;
	char **key = get_keys(data->envp);
	char **value = get_value(data->envp);
	data->export_lst = NULL;
    while(data->envp[i])
    {
        add_back(&data->export_lst, ft_newnode(add_quoutes(data->envp[i]), key[i], value[i]));
		if(ft_strcmp(key[i], "PWD") == 0)
			add_back(&data->export_lst, ft_newnode(ft_strdup("OLDPWD"), ft_strdup("OLDPWD"), NULL));
        i++;
    }
}

void    print_export(t_data data)
{
    t_env *export_lst = data.export_lst;
	while(export_lst)
	{
		printf("declare -x ");
		printf("%s\n", export_lst->content);
		export_lst = export_lst->next;
    }
}

int is_quouted(char *value)
{
	int i = 0;
	if(!value)
		return(0);
	while(value[i])
	{
		if(value[i] == '=')
		{
			i++;
			if(value[i] == '"')
			{
				i++;
				while(value[i] != '"' && value[i] != '\0')
					i++;
				if(value[i] == '"')
					return(1);
			}
		}
	}
	return(0);
}
void	export_commands(t_data *data)
{
	int i = 1;
	char **var;
	char *key_cmd;
	char *value_cmd;
	while(data->cmd_lst->commands[i])
	{
		var = ft_split(data->cmd_lst->commands[i], '=');
		key_cmd = var[0];
		value_cmd = ft_strchr(data->cmd_lst->commands[i], '=');
    	add_to_env_export(data, key_cmd, value_cmd);
		i++;
	}
}

void	add_to_export_lst(t_data *data, char *key, char *value)
{
	t_env *export_tmp = data->export_lst;
	char *content;
	if(is_quouted(value))
		content = ft_strdup(data->cmd_lst->commands[1]);
	else
		content = add_quoutes(data->cmd_lst->commands[1]);
	while(export_tmp)
	{
		if(ft_strncmp(export_tmp->key, key, ft_strlen(key)) == 0)
		{
			free(export_tmp->value);
			export_tmp->value = ft_strdup(value);
			export_tmp->content = content;
			return ;
		}
		else
			export_tmp = export_tmp->next;
	}
	add_back(&data->export_lst, ft_newnode(content, key, ft_strdup(value)));
}
