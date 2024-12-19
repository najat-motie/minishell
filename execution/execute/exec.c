/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:22:15 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/19 22:04:03 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_command(t_data *data, t_cmd *tmp, t_fd *fd, int i)
{
	char	*path;

	if (!is_builtin(tmp->commands[0]))
	{
		path = get_path(*data, tmp->commands[0]);
		check_path(path, tmp->commands[0]);
	}
	set_input_and_output(tmp, fd);
	set_read_write_pipe(*data, tmp, fd, i);
	if (is_builtin(tmp->commands[0]))
	{
		handle_builtins(data, tmp->commands);
		exit(EXIT_SUCCESS);
	}
	else
	{
		execve(path, tmp->commands, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	handle_child(t_data *data, t_cmd *tmp, t_fd *fd, int i)
{
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
	{
		perror("signal");
		exit(EXIT_FAILURE);
	}
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
	{
		perror("signal");
		exit(EXIT_FAILURE);
	}
	if (tmp->input_fd == -1 || tmp->output_fd == -1)
		exit(EXIT_FAILURE);
	execute_command(data, tmp, fd, i);
}

void	handle_childs(t_data *data, t_fd *fd)
{
	int		i;
	int		*pids;
	t_cmd	*tmp;

	i = 0;
	tmp = data->cmd_lst;
	pids = malloc(data->cmd_nb * sizeof(int));
	while (1)
	{
		if (!create_pipe(data, fd, i))
			return ;
		pids[i] = fork();
		if (pids[i] == 0)
			handle_child(data, tmp, fd, i);
		else if (pids[i] == -1)
		{
			clear_ressources(pids, fd, &i);
			return ;
		}
		else
			save_read_of_pipe(*data, fd, i);
		if (!move_to_next_cmd(*data, &tmp, &i))
			break ;
	}
	wait_pids(data, pids);
}

void	excute_commands(t_data *data)
{
	t_fd	fd;

	fd.prev_fd = -1;
	if (signal(SIGQUIT, handle_sigquit_in_child) == SIG_ERR)
	{
		perror("signal");
		return ;
	}
	if (signal(SIGINT, sigint_parent_change_behavior_in_child) == SIG_ERR)
	{
		perror("signal");
		return ;
	}
	handle_childs(data, &fd);
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
	{
		perror("signal");
		return ;
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("signal");
		return ;
	}
}
