/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 01:49:53 by ner-roui          #+#    #+#             */
/*   Updated: 2024/12/24 21:05:57 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	fill_cmd(t_data *data, t_token *tmp)
{
	data->cmd_lst->prev->commands = get_param(data, tmp);
	if (!data->cmd_lst->prev->commands)
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	if (!get_here_doc(data, tmp, data->cmd_lst->prev)
		&& data->cmd_lst->prev->here_doc != -1)
		return (false);
	if (!get_infile(data, tmp, data->cmd_lst->prev)
		&& data->cmd_lst->prev->input_fd != -1)
		return (false);
	if (!get_outfile(tmp, data->cmd_lst->prev, data)
		&& data->cmd_lst->prev->output_fd != -1)
		return (false);
	if (data->cmd_lst->prev->input_fd == -1)
	{
		data->cmd_lst->prev->output_fd = -1;
		return (true);
	}
	if (data->cmd_lst->prev->output_fd == -1)
	{
		if (data->cmd_lst->prev->input_fd >= 0)
			close(data->cmd_lst->prev->input_fd);
		data->cmd_lst->prev->input_fd = -1;
		return (true);
	}
	return (true);
}

static bool	norm(t_data *data, t_token *tmp)
{
	if (!append_cmd(&data->cmd_lst, -2, -2, NULL))
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	if (!fill_cmd(data, tmp))
	{
		data->exit_status = 2;
		return (false);
	}
	return (true);
}

bool	create_list_cmd(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	if (!norm(data, tmp))
		return (false);
	tmp = tmp->next;
	while (tmp != data->token)
	{
		if (tmp->prev->type == PIPE)
		{
			if (!norm(data, tmp))
				return (false);
		}
		tmp = tmp->next;
	}
	return (true);
}
