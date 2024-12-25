/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:45:37 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/24 12:57:48 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	clear_ressources(int *pid, t_fd *fd, int *i)
{
	if (fd->prev_fd != -2)
		close(fd->prev_fd);
	close(fd->read_pipe);
	close(fd->write_pipe);
	perror("fork");
	while (*i - 1 >= 0)
	{
		kill(pid[*i], SIGKILL);
		(*i)--;
	}
}

int	commands_numbr(t_data data)
{
	int		nb;
	t_cmd	*tmp;

	nb = 0;
	tmp = data.cmd_lst;
	if (tmp)
	{
		nb++;
		tmp = tmp->next;
	}
	while (tmp != data.cmd_lst)
	{
		nb++;
		tmp = tmp->next;
	}
	return (nb);
}

int	move_to_next_cmd(t_data data, t_cmd **tmp, int *i)
{
	(*i)++;
	*tmp = (*tmp)->next;
	if (*tmp == data.cmd_lst)
		return (0);
	return (1);
}

void	wait_pids(t_data *data, int *pids)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->cmd_nb)
	{
		if (waitpid(pids[i], &status, 0) == -1)
		{
			perror("waitpid");
			data->exit_status = 1;
			return ;
		}
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->exit_status = WTERMSIG(status) + 128;
		i++;
	}
	free(pids);
}
