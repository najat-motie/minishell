/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:22:19 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/24 21:08:51 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*check_current_working_directory(char *command)
{
	char	*path;
	char	*pwd;

	pwd = get_pwd();
	if (!pwd)
	{
		perror("getcwd");
		return (NULL);
	}
	path = ft_strjoin(ft_strjoin(pwd, "/"), command);
	free(pwd);
	if (access(path, X_OK) == 0)
		return (path);
	else
	{
		free(path);
		perror(command);
		return (NULL);
	}
}

char	*search_path(char *path, char *command)
{
	int		i;
	char	*full_path;
	char	**all_paths;

	i = 0;
	all_paths = ft_split(path, ':');
	while (all_paths != NULL && all_paths[i] != NULL)
	{
		full_path = ft_strjoin(ft_strjoin(all_paths[i], "/"), command);
		if (access(full_path, X_OK) == 0)
		{
			path = ft_strdup(full_path);
			ft_free(all_paths);
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	*get_path_of_command(t_data data, char *command)
{
	char	*path;
	char	*get_path;

	path = retreive_value(data, "PATH");
	if (path == NULL)
	{
		path = check_current_working_directory(command);
		if (path)
			return (path);
		return (NULL);
	}
	get_path = search_path(path, command);
	if (get_path)
		return (get_path);
	else
		return ("not valid command");
}

char	*get_path(t_data data, char *command)
{
	struct stat	check_stat;

	if (!command)
		return (NULL);
	if (ft_strchr(command, '/') != NULL || (command[0] == '.'
			&& command[1] == '/'))
	{
		stat(command, &check_stat);
		if (S_ISDIR(check_stat.st_mode))
			return ("it's a directory");
		else if (access(command, X_OK) == 0)
			return (command);
		else if (access(command, F_OK) == 0)
			return ("don't have execute permission");
		else
		{
			perror(command);
			return (NULL);
		}
	}
	return (get_path_of_command(data, command));
}

void	check_path(char *path, char *command)
{
	if (ft_strcmp(path, "don't have execute permission") == 0)
	{
		write(2, "minishell: ", 11);
		write(2, command, ft_strlen(command));
		write(2, ": Permission denied\n", 20);
		exit(126);
	}
	else if (ft_strcmp(path, "it's a directory") == 0)
	{
		write(2, "minishell: ", 11);
		write(2, command, ft_strlen(command));
		write(2, ": is a directory\n", 17);
		exit(126);
	}
	else if (ft_strcmp(path, "not valid command") == 0)
	{
		write(2, "minishell: ", 11);
		write(2, command, ft_strlen(command));
		write(2, ": command not found\n", 20);
		exit(127);
	}
	else if (!path && command)
		exit(127);
	else if (!path && !command)
		exit(EXIT_SUCCESS);
}
