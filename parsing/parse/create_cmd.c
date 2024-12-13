#include "../../minishell.h"

static bool	fill_cmd(t_data *data, t_token *tmp)
{
	if (!get_infile(data, tmp, data->cmd_lst->prev) && \
		data->cmd_lst->prev->input_fd != -1)
		return (false);
	if (data->cmd_lst->prev->input_fd == -1)
	{
		data->cmd_lst->prev->skip_cmd = true;
		data->cmd_lst->prev->output_fd = -1;
		return (true);
	}
	if (!get_outfile(tmp, data->cmd_lst->prev, data) && data->cmd_lst->prev->output_fd \
		!= -1)
		return (false);
	if (data->cmd_lst->prev->output_fd == -1)
	{
		if (data->cmd_lst->prev->input_fd >= 0)
			close (data->cmd_lst->prev->input_fd);
		data->cmd_lst->prev->skip_cmd = true;
		data->cmd_lst->prev->input_fd = -1;
		return (true);
	}
	data->cmd_lst->prev->commands = get_param(data, tmp);
	if (!data->cmd_lst->prev->commands)
		free_all(data, ERR_MALLOC, EXT_MALLOC);
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
