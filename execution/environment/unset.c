#include "../../minishell.h"

void	remove_from_lst(t_data *data, char *key)
{
	t_env	*tmp;
	t_env	*env_lst;

	env_lst = data->env_lst;
	while (env_lst && env_lst->next)
	{
		if (ft_strcmp(env_lst->next->str, key) == 0)
		{
			tmp = env_lst->next;
			env_lst->next = tmp->next;
			free(tmp);
			return ;
		}
		env_lst = env_lst->next;
	}
}

void	unset_variables(t_data *data, char **key)
{
	int i = 1;
	while (key[i])
	{
		if(!not_valid(key[i]))
			remove_from_lst(data, key[i]);
		i++;
	}
}
