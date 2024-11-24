#include "../minishell.h"

t_env	*ft_new_env(char *key, char *value, int equal)
{
	t_env	*newnode;

	newnode = malloc(sizeof(t_env));
	if (newnode == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	newnode->key = key;
	newnode->value = value;
	newnode->equal = equal;
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

int there_equal(char *command)
{
	int i = 0;
	while(command[i])
	{
		if(command[i] == '=')
			return(1);
		i++;
	}
	return(0);
}

char **get_keys(char **envp)
{
	int i = 0;
	while(envp[i])
		i++;
	char **key = malloc((i + 1) * sizeof(char *));
	if(key == NULL)
	{
		perror("malloc");
		return(NULL);
	}
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
	{
		perror("malloc");
		return(NULL);
	}
	i = 0;
	char **var;
	while(envp[i])
	{
		var = ft_split(envp[i], '=');
		value[i] = var[1];
		i++;
	}
	value[i] = NULL;
	return(value);
}

void    print_env(t_data *data)
{
    t_env *tmp_lst = data->env_lst;
	while(tmp_lst)
	{
		printf("%s", tmp_lst->key);
        if(tmp_lst->value)
		    printf("=%s\n", tmp_lst->value);
        else
            printf("\n");
		tmp_lst = tmp_lst->next;
    }
    data->exit_status = 0;
}
