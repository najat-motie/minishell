/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:21:57 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/24 12:47:14 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_previos(char *key_cmd, t_env *envp_tmp)
{
	free(key_cmd);
	free(envp_tmp->value);
	free(envp_tmp->str);
}

void	add_to_lst(t_data *data, char **commands, int equal, int *i)
{
	char	**var;
	char	*key_cmd;
	char	*value_cmd;
	t_env	*envp_tmp;

	envp_tmp = data->env_lst;
	var = ft_split(commands[*i], '=');
	key_cmd = var[0];
	value_cmd = var[1];
	free(var);
	while (envp_tmp)
	{
		if (ft_strcmp(envp_tmp->key, key_cmd) == 0)
		{
			free_previos(key_cmd, envp_tmp);
			envp_tmp->equal = equal;
			envp_tmp->value = value_cmd;
			envp_tmp->str = ft_strdup(commands[*i]);
			return ;
		}
		else
			envp_tmp = envp_tmp->next;
	}
	add_back_env(&data->env_lst, ft_new_env(key_cmd, value_cmd, equal,
			ft_strdup(commands[*i])));
}

void	export_variables(t_data *data, char **commands)
{
	int	i;
	int	equal;

	i = 1;
	equal = 0;
	while (commands[i])
	{
		if (there_equal(commands[i]))
			equal = 1;
		if (not_valid(commands[i]))
			return ;
		else
			add_to_lst(data, commands, equal, &i);
		i++;
	}
}
// strdup------->0x7f825e004140
// strdup------->0x7f825e004140
// strdup------->0x7f825e0040c0
// split1------->0x7f825e004310
// split2------->0x7f825e004320
// strdup------->0x7f825e004320
