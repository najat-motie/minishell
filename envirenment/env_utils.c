#include "../minishell.h"

t_env	*ft_new_env(char *content, char *key, char *value)
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

void	add_back_env(t_env **lst, t_env *new)
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
