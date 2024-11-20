#include "../minishell.h"

void    fill_env_lst(t_data *data)
{
    int i = 0;
	char **key = get_keys(data->envp);
	char **value = get_value(data->envp);
	data->env_lst = NULL;
    while(data->envp[i])
    {
        add_back_env(&data->env_lst, ft_new_env(data->envp[i], key[i], value[i]));
        i++;
    }
}

void	add_to_env_lst(t_data *data, char *key, char *value, char *command)
{
	t_env *envp_tmp = data->env_lst;
	while(envp_tmp)
	{
		if(ft_strcmp(envp_tmp->key, key) == 0)
		{
			free(envp_tmp->value);
			envp_tmp->value = ft_strdup(value);
			envp_tmp->content = ft_strdup(command);
			return ;
		}
		else
			envp_tmp = envp_tmp->next;
	}
	add_back_env(&data->env_lst, ft_new_env(command, key, value));
}
