/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:22:02 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/14 16:31:14 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_old_pwd(t_env *env_tmp, t_env *tmp, char *value)
{
	t_env *new_node;

	new_node = ft_new_env("OLDPWD", value, 1, ft_strjoin("OLDPWD", value));
	env_tmp->next = new_node;
	new_node->next = tmp;
	tmp = NULL;
}

void	update_old_pwd(t_data *data)
{
	char *value;
	t_env *tmp;
	t_env *env_tmp;

	value = get_pwd();
	env_tmp = data->env_lst; 
	while(env_tmp)
	{
		if(ft_strcmp(env_tmp->key, "PWD") == 0)
		{
			tmp = env_tmp->next;
			if(ft_strcmp(tmp->key, "OLDPWD") == 0)
			{
				tmp->value = value;
				env_tmp->str = ft_strjoin("OLDPWD", value);
			}
			else
				add_old_pwd(env_tmp, tmp, value);
			return;
		}
		env_tmp = env_tmp->next;
	}
}

void	update_new_pwd(t_data *data)
{
	char *value;

    value = get_pwd();
	t_env *env_tmp = data->env_lst;
	while(env_tmp)
	{
		if(ft_strcmp(env_tmp->key, "PWD") == 0)
		{
			free(env_tmp->value);
			env_tmp->value = value;
			env_tmp->str = ft_strjoin("OLDPWD", value);
			break ;
		}
		env_tmp = env_tmp->next;
	}
}
