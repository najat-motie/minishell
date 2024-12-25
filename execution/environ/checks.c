/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:21:51 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/24 17:30:34 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_errors(char **commands, int *i)
{
	write(2, "minishell: ", 11);
	write(2, commands[0], ft_strlen(commands[0])); 
	write(2, ": `", 3);
	write(2, commands[*i], ft_strlen(commands[*i]));
	write(2, "': not a valid identifier\n", 26);
}

int	check_other_characters(char *command)
{
	int	j;

	j = 1;
	while (command[j] && command[j] != '=')
	{
		if ((command[j] < 'a' || command[j] > 'z') && (command[j] < 'A'
				|| command[j] > 'Z') && (command[j] < '0' || command[j] > '9')
			&& command[j] != '_')
			return (1);
		j++;
	}
	return (0);
}

int	not_valid(char *command)
{
	if ((command[0] < 'a' || command[0] > 'z') && (command[0] < 'A'
			|| command[0] > 'Z') && command[0] != '_')
		return (1);
	if (check_other_characters(command))
		return (1);
	return (0);
}

void	check_not_valid_variables(t_data *data, char **commands)
{
	int	i;

	i = 1;
	while (commands[i])
	{
		if ((commands[i][0] < 'a' || commands[i][0] > 'z')
			&& (commands[i][0] < 'A' || commands[i][0] > 'Z')
			&& commands[i][0] != '_')
		{
			print_errors(commands, &i);
			data->exit_status = 1;
		}
		else if (check_other_characters(commands[i]))
		{
			print_errors(commands, &i);
			data->exit_status = 1;
		}
		i++;
	}
}
