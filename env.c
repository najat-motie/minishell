#include "minishell.h"

t_env	*ft_newnode(char *content, char *key, char *value)
{
	t_env	*newnode;

	newnode = malloc(sizeof(t_env));
	if (newnode == NULL)
		return (NULL);
	newnode->content = ft_strdup(content);
	newnode->key = key;
	newnode->value = ft_strdup(value);
	newnode->next = NULL;
	return (newnode);
}

void	add_back(t_env **lst, t_env *new)
{
	t_env	*node;
	
	if (*lst == NULL)
		*lst = new;
	else
	{
		node = *lst;
		while (node->next != NULL)
			node = node->next;
		node->next = new;
	}
}

char **get_keys(char **envp)
{
	int i = 0;
	while(envp[i])
		i++;
	char **key = malloc((i + 1) * sizeof(char *));
	if(key == NULL)
		return(NULL);
	i = 0;
	char **var;
	while(envp[i])
	{
		var = ft_split(envp[i], '=');
		key[i] = var[0];
		i++;
	}
	key[i] = NULL;
	return(key);
}

char **get_value(char **envp)
{
	int i = 0;
	while(envp[i])
		i++;
	char **value = malloc((i + 1) * sizeof(char *));
	if(value == NULL)
		return(NULL);
	i = 0;
	char *var;
	while(envp[i])
	{
		var = ft_strchr(envp[i], '=');
		value[i] = var;
		i++;
	}
	value[i] = NULL;
	return(value);
}

void    fill_env_lst(t_data *data)
{
    int i = 0;
	char **key = get_keys(data->envp);
	char **value = get_value(data->envp);
	data->env_lst = NULL;
    while(data->envp[i])
    {
        add_back(&data->env_lst, ft_newnode(data->envp[i], key[i], value[i]));
        i++;
    }
}

void    print_env(t_data data)
{
    t_env *env_lst = data.env_lst;
	while(env_lst)
	{
		printf("%s\n", env_lst->content);
		env_lst = env_lst->next;
    }
}

void	add_to_env_lst(t_data *data, char *key, char *value, char *command)
{
	t_env *envp_tmp = data->env_lst;
	while(envp_tmp)
	{
		if(ft_strncmp(envp_tmp->key, key, ft_strlen(key)) == 0)
		{
			free(envp_tmp->value);
			envp_tmp->value = ft_strdup(value);
			envp_tmp->content = ft_strdup(command);
			return ;
		}
		else
			envp_tmp = envp_tmp->next;
	}
	add_back(&data->env_lst, ft_newnode(command, key, value));
}

void	add_to_env_export(t_data *data, char *key, char *value, char *command)
{
	if(value)
	{
		add_to_env_lst(data, key, value, command);
		add_to_export_lst(data, key, value, command);
	}
	else
		add_to_export_lst(data, key, value, command);
}