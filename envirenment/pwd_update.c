#include "../minishell.h"

void	update_old_pwd(t_data *data)
{
	t_env *tmp;
	t_env *new_node;
	t_env *env_tmp;

	char value[1024];
    if(!getcwd(value, sizeof(value)))
    	perror("getcwd");
	env_tmp = data->env_lst; 
	while(env_tmp)
	{
		if(ft_strcmp(env_tmp->key, "PWD") == 0)
		{
			tmp = env_tmp->next;
			if(ft_strcmp(tmp->key, "OLDPWD") == 0)
				tmp->value = ft_strdup(value);
			else
			{
				new_node = ft_new_env("OLDPWD", ft_strdup(value), 1);
				env_tmp->next = new_node;
				new_node->next = tmp;
				tmp = NULL;
			}
			return;
		}
		env_tmp = env_tmp->next;
	}
}

void	update_new_pwd(t_data *data)
{
	char value[1024];
    if(!getcwd(value, sizeof(value)))
    	perror("getcwd");
	t_env *env_tmp = data->env_lst;
	while(env_tmp)
	{
		if(ft_strcmp(env_tmp->key, "PWD") == 0)
		{
			free(env_tmp->value);
			env_tmp->value = ft_strdup(value);
			break ;
		}
		env_tmp = env_tmp->next;
	}
}
