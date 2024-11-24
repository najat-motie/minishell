#include "../../minishell.h"

int check_args(char *command)
{
	int j = 1;

	if ((command[j] < 'a' || command[j] > 'z')
		&& (command[j] < 'A' || command[j] > 'Z')
		&& (command[j] < 'j' || command[j] > '9')
		&& command[j] != '_' && command[j] != '=')
		return(1);
	return(0);
}

int	not_valid_unset(char **commands)
{
	int	i;

	i = 1;
	while (commands[i])
	{
		if ((commands[i][0] < 'a' || commands[i][0] > 'z')
			&& (commands[i][0] < 'A' || commands[i][0] > 'Z')
			&& commands[i][0] != '_')
		{
			printf("unset: `%s': not a valid identifier\n", commands[i]);
			return (1);
		}
		while (commands[i])
		{
			if (check_args(commands[i]))
			{
				printf("unset: `%s': not a valid identifier\n", commands[i]);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void	remove_from_lst(t_data *data, char *key)
{
	t_env	*tmp;
	t_env	*env_lst;

	env_lst = data->env_lst;
	while (env_lst && env_lst->next)
	{
		if (ft_strcmp(env_lst->next->key, key) == 0)
		{
			tmp = env_lst->next;
			env_lst->next = tmp->next;
			free(tmp);
			return ;
		}
		env_lst = env_lst->next;
	}
}

void	unset_commands(t_data *data, char **key)
{
	int i = 1;
	while (data->cmd_lst->commands[i])
	{
		remove_from_lst(data, key[i]);
		i++;
	}
}