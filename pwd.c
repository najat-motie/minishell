#include "minishell.h"

char *update_content_in_pwd(char *key, char *value)
{
	char *content = malloc(ft_strlen(key) + ft_strlen(value) + 2);
	if(!content)
		return(NULL);
	int i = 0;
	while(key[i])
	{
		content[i] = key[i];
		i++;
	}
	content[i++] = '=';
	int j = 0;
	while(value[j])
		content[i++] = value[j++];
	content[i++] = '\0';
	return(content);
}

char *update_content_with_quoutes(char *key, char *value)
{
	char *content = malloc(ft_strlen(key) + ft_strlen(value) + 4);
	if(!content)
		return(NULL);
	int i = 0;
	while(key[i])
	{
		content[i] = key[i];
		i++;
	}
	content[i++] = '=';
	content[i++] = '"';
	int j = 0;
	while(value[j])
		content[i++] = value[j++];
	content[i++] = '"';
	content[i++] = '\0';
	return(content);
}

void	update_new_pwd(t_data *data)
{
	t_env *env_tmp = data->env_lst;
	t_env *export_tmp = data->export_lst;
	char cwd[1024];
    if(!getcwd(cwd, sizeof(cwd)))
    	perror("pwd");
	while(env_tmp)
	{
		if(ft_strcmp(env_tmp->key, "PWD") == 0)
		{
			env_tmp->content = update_content_in_pwd("PWD", cwd);
			break ;
		}
		env_tmp = env_tmp->next;
	}
	while(export_tmp)
	{
		if(ft_strcmp(export_tmp->key, "PWD") == 0)
		{
			export_tmp->content = update_content_with_quoutes("PWD", cwd);
			break ;
		}
		export_tmp = export_tmp->next;
	}
}

void	update_old_pwd_env(t_data *data, char *value)
{
	t_env *env_tmp = data->env_lst;
	char *content_env = update_content_in_pwd("OLDPWD", value); 
	t_env *tmp;             
	while(env_tmp)
	{
		if(ft_strcmp(env_tmp->key, "PWD") == 0)
		{
			tmp = env_tmp->next;
			if(ft_strcmp(tmp->key, "OLDPWD") == 0)
			{
				tmp->content = content_env;
				return ;
			}
			else
			{
				t_env *new_node = ft_newnode(content_env, "OLDPWD", ft_strchr(content_env, '='));
				env_tmp->next = new_node;
				new_node->next = tmp;
				tmp = NULL;
				return ;
			}
		}
		env_tmp = env_tmp->next;
	}
}

void	update_old_pwd_export(t_data *data, char *value)
{
	t_env *export_tmp = data->export_lst;        
	char *content_export = update_content_with_quoutes("OLDPWD", value);
	t_env *tmp;             
	while(export_tmp)
	{
		if(ft_strcmp(export_tmp->key, "PWD") == 0)
		{
			tmp = export_tmp->next;
			if(ft_strcmp(tmp->key, "OLDPWD") == 0)
			{
				tmp->content = content_export;
				return ;
			}
			else
			{
				t_env *new_node = ft_newnode(content_export, "OLDPWD", ft_strchr(content_export, '='));
				export_tmp->next = new_node;
				new_node->next = tmp;
				tmp = NULL;
				return ;
			}
		}
		export_tmp = export_tmp->next;
	}
}

void	update_old_pwd(t_data *data)
{
	char cwd[1024];
    if(!getcwd(cwd, sizeof(cwd)))
    	perror("pwd");
	update_old_pwd_env(data, cwd);
	update_old_pwd_export(data, cwd);
}
	
