/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:21:54 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/24 12:36:25 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*ft_new_env(char *key, char *value, int equal, char *str)
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
	newnode->str = str;
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

void	make_env(t_data *data, char **envp)
{
	int		i;
	char	**key;
	char	**value;

	i = 0;
	key = get_keys(envp);
	value = get_value(envp);
	while (envp[i])
	{
		add_back_env(&data->env_lst, ft_new_env(key[i], value[i], 1,
				ft_strdup(envp[i])));
		i++;
	}
	free(key);
	free(value);
}

void	clear_env(t_env **lst)
{
	t_env	*node;
	t_env	*save_next;

	if (lst == NULL || *lst == NULL)
		return ;
	node = *lst;
	while (node != NULL)
	{
		save_next = node->next;
		free(node->key);
		free(node->value);
		free(node->str);
		free(node);
		node = save_next;
	}
	*lst = NULL;
}
