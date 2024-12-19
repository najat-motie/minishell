/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:21:38 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/19 23:49:30 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_only(char **commands)
{
	if (commands[0] != NULL)
	{
		if (ft_strcmp(commands[0], "cd") == 0 || ft_strcmp(commands[0],
				"exit") == 0 || (ft_strcmp(commands[0], "export") == 0
				&& commands[1] != NULL) || (ft_strcmp(commands[0], "unset") == 0
				&& commands[1] != NULL))
			return (1);
	}
	return (0);
}

int	is_nemuric(char *command)
{
	int	i;

	i = 0;
	if (command[0] == '-')
		i++;
	while (command[i])
	{
		if (command[i] < '0' || command[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	get_status(char **commands)
{
	if (is_nemuric(commands[1]))
	{
		if (commands[1] && !commands[2])
		{
			if (ft_atoi(commands[1]) > 0)
			{
				printf("exit\n");
				exit(ft_atoi(commands[1]));
			}
			else
			{
				printf("exit\n");
				exit(256 + ft_atoi(commands[1]));
			}
		}
		else
			printf("exit\nminishell: exit: too many arguments\n");
	}
	else
	{
		printf("exit\nminishell: exit: %s: numeric argument required\n",
			commands[1]);
		exit(255);
	}
}
