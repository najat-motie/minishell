/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:21:38 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/24 17:38:48 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_err(char *command)
{
	write(2, "exit\nminishell: exit: ", 22);
	write(2, command, ft_strlen(command));
	write(2, ": numeric argument required\n", 28);
	exit(255);
}

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
	if (command[0] == '-' || command[0] == '+')
		i++;
	while (command[i])
	{
		if (command[i] < '0' || command[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	get_status(t_data *data, char **commands)
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
		{
			write(2, "exit\nminishell: exit: too many arguments\n", 41);
			data->exit_status = 1;
		}
	}
	else
		exit_err(commands[1]);
}
