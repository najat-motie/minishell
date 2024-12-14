/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:21:57 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/14 16:21:59 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_to_lst(t_data *data, char **commands, int equal, int *i)
{
	char	**var;
	t_env	*envp_tmp;
	char	*key_cmd;
	char	*value_cmd;

	envp_tmp = data->env_lst;
	var = ft_split(commands[*i], '=');
	key_cmd = var[0];
	value_cmd = var[1];
	while (envp_tmp)
	{
		if (ft_strcmp(envp_tmp->key, key_cmd) == 0)
		{
			free(envp_tmp->value);
			envp_tmp->value = value_cmd;
			return ;
		}
		else
			envp_tmp = envp_tmp->next;
	}
	add_back_env(&data->env_lst, ft_new_env(key_cmd, value_cmd, equal, commands[*i]));
}

void	export_variables(t_data *data, char **commands)
{
	int		i;
	int		equal;

	i = 1;
	equal = 0;
	while (commands[i])
	{
		if (there_equal(commands[i]))
			equal = 1;
		if(not_valid(commands[i]))
			return ;
		else
			add_to_lst(data, commands, equal, &i);
		i++;
	}
}
