/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ner-roui <ner-roui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:22:25 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/23 01:44:27 by ner-roui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	set_input_and_output(t_cmd *tmp, t_fd *fd)
{
	if (tmp->input_fd != -2)
	{
		close(fd->read_pipe);
		if (dup2(tmp->input_fd, 0) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(tmp->input_fd);
	}
	if (tmp->output_fd != -2)
	{
		close(fd->write_pipe);
		if (dup2(tmp->output_fd, 1) < 0)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(tmp->output_fd);
	}
}

void	set_read_write_pipe(t_data data, t_cmd *tmp, t_fd *fd, int i)
{
	if (i > 0 && tmp->input_fd == -2)
	{
		if (dup2(fd->prev_fd, 0) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(fd->prev_fd);
	}
	if (i < data.cmd_nb - 1 && tmp->output_fd == -2)
	{
		close(fd->read_pipe);
		if (dup2(fd->write_pipe, 1) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(fd->write_pipe);
	}
}

void	save_read_of_pipe(t_data data, t_fd *fd, int i)
{
	if (fd->prev_fd != -2)
		close(fd->prev_fd);
	if (i < data.cmd_nb - 1)
	{
		close(fd->write_pipe);
		fd->prev_fd = fd->read_pipe;
	}
}

int	create_pipe(t_data *data, t_fd *fd_, int i)
{
	int	fd[2];

	if (i < data->cmd_nb - 1)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			data->exit_status = 1;
			return (0);
		}
	}
	fd_->read_pipe = fd[0];
	fd_->write_pipe = fd[1];
	return (1);
}
