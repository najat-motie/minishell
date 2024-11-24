#include "../../minishell.h"

int	not_valid_export(char **commands)
{
	int	i;

	i = 1;
	while (commands[i])
	{
		if ((commands[i][0] < 'a' || commands[i][0] > 'z')
			&& (commands[i][0] < 'A' || commands[i][0] > 'Z')
			&& commands[i][0] != '_')
		{
			printf("export: `%s': not a valid identifier\n", commands[i]);
			return (1);
		}
		while (commands[i])
		{
			if (check_args(commands[i]))
			{
				printf("export: `%s': not a valid identifier\n", commands[i]);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void	fill_env_lst(t_data *data)
{
	int		i;
	char	**key;
	char	**value;

	i = 0;
	key = get_keys(data->envp);
	value = get_value(data->envp);
	data->env_lst = NULL;
	while (data->envp[i])
	{
		add_back_env(&data->env_lst, ft_new_env(key[i], value[i], 1));
		i++;
	}
}

void	add_to_lst(t_data *data, char *key, char *value, int equal)
{
	t_env	*envp_tmp;

	envp_tmp = data->env_lst;
	while (envp_tmp)
	{
		if (ft_strcmp(envp_tmp->key, key) == 0)
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
	int		i;
	int		equal;
	char	**var;
	char	*key_cmd;
	char	*value_cmd;

	i = 1;
	equal = 0;
	while (commands[i])
	{
		if (there_equal(commands[i]))
			equal = 1;
		var = ft_split(commands[i], '=');
		key_cmd = var[0];
		value_cmd = var[1];
		add_to_lst(data, key_cmd, value_cmd, equal);
		i++;
	}
}
