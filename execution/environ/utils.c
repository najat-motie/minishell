/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:22:08 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/24 14:36:15 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	s = NULL;
}

int	there_equal(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	**get_keys(char **envp)
{
	int		i;
	char	**key;
	char	**var;

	i = 0;
	while (envp[i])
		i++;
	key = malloc((i + 1) * sizeof(char *));
	if (key == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	i = 0;
	while (envp[i])
	{
		var = ft_split(envp[i], '=');
		key[i] = ft_strdup(var[0]);
		ft_free(var);
		i++;
	}
	key[i] = NULL;
	return (key);
}

char	**get_value(char **envp)
{
	int		i;
	char	**value;
	char	**var;

	i = 0;
	while (envp[i])
		i++;
	value = malloc((i + 1) * sizeof(char *));
	if (value == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	i = 0;
	while (envp[i])
	{
		var = ft_split(envp[i], '=');
		value[i] = ft_strdup(var[1]);
		ft_free(var);
		i++;
	}
	value[i] = NULL;
	return (value);
}

char	*retreive_value(t_data data, char *key)
{
	t_env	*env_tmp;

	env_tmp = data.env_lst;
	while (env_tmp)
	{
		if (ft_strcmp(env_tmp->key, key) == 0)
			return (env_tmp->value);
		env_tmp = env_tmp->next;
	}
	return (NULL);
}
