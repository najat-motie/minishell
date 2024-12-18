#include "../../minishell.h"

void	make_env(t_data *data, char **envp)
{
	int		i;
	char	**key;
	char	**value;

	i = 0;
	key = get_keys(envp);
	value = get_value(envp);
	// printf("-->%s\n",envp[0]);
	// data->env_lst = NULL;
	while (envp[i])
	{
		add_back_env(&data->env_lst, ft_new_env(key[i], value[i], 1, envp[i]));
		i++;
	}
}

char *retreive_value(t_data data, char *key)
{
    t_env *env_tmp = data.env_lst;

    while(env_tmp)
    {
        if(ft_strcmp(env_tmp->key, key) == 0)
            return(env_tmp->value);           
        env_tmp = env_tmp->next;
    }
    return(NULL);
}
