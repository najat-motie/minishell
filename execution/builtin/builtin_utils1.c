/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:21:35 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/19 20:40:08 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return (NULL);
	}
	return (ft_strdup(cwd));
}

void	change_to_home(t_data *data)
{
	char	*home;

	home = retreive_value(*data, "HOME");
	if (home == NULL)
	{
		printf("minishell: cd: HOME not set\n");
		data->exit_status = 1;
	}
	else if (chdir(home) != 0)
	{
		perror("chdir");
		data->exit_status = 1;
	}
	else
		data->exit_status = 0;
}

void	change_dir(t_data *data)
{
	if (data->cmd_lst->commands[1] != NULL)
	{
		if (chdir(data->cmd_lst->commands[1]) != 0)
		{
			perror("chdir");
			data->exit_status = 1;
		}
		else
			data->exit_status = 0;
	}
	else
		change_to_home(data);
}

void	handle_newline_case(char **commands, int *newline, int *i)
{
	int	j;

	if (commands[1] != NULL)
	{
		if (commands[1][0] == '-' && commands[1][1] == 'n')
		{
			j = 1;
			while (commands[1][j] == 'n')
				j++;
			if (commands[1][j] == '\0')
			{
				*newline = 0;
				(*i)++;
			}
		}
	}
}

void	print_args(char **commands)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	handle_newline_case(commands, &newline, &i);
	while (commands[i] != NULL)
	{
		printf("%s", commands[i]);
		i++;
		if (commands[i])
			printf(" ");
	}
	if (newline)
		printf("\n");
}
