#include "../minishell.h"

void	update_new_pwd_env(t_data *data, char *value)
{
	t_env *env_tmp = data->env_lst;
	while(env_tmp)
	{
		if(ft_strcmp(env_tmp->key, "PWD") == 0)
		{
			env_tmp->content = ft_strjoin("PWD", value);
			break ;
		}
		env_tmp = env_tmp->next;
	}
}

void	update_new_pwd_export(t_data *data, char *value)
{
	t_env *export_tmp = data->export_lst;
	while(export_tmp)
	{
		if(ft_strcmp(export_tmp->key, "PWD") == 0)
		{
			export_tmp->content = add_quoutes("PWD", value);
			break ;
		}
		export_tmp = export_tmp->next;
	}
}

void	update_old_pwd_env(t_data *data, char *value)
{
	t_env *env_tmp;
	t_env *tmp;
	t_env *new_node;
	char *content_env; 

	env_tmp = data->env_lst; 
	content_env = ft_strjoin("OLDPWD", value);             
	while(env_tmp)
	{
		if(ft_strcmp(env_tmp->key, "PWD") == 0)
		{
			tmp = env_tmp->next;
			if(ft_strcmp(tmp->key, "OLDPWD") == 0)
				tmp->content = content_env;
			else
			{
				new_node = ft_new_env(content_env, "OLDPWD", value);
				env_tmp->next = new_node;
				new_node->next = tmp;
				tmp = NULL;
			}
			return;
		}
		env_tmp = env_tmp->next;
	}
}

void	update_old_pwd_export(t_data *data, char *value)
{
	t_env *export_tmp = data->export_lst;        
	char *content_export = add_quoutes("OLDPWD", value);
	while(export_tmp)
	{
		if(ft_strcmp(export_tmp->key, "OLDPWD") == 0)
		{
			export_tmp->content = content_export;
			return ;
		}
		else
			export_tmp = export_tmp->next;
	}
}