#include "../../minishell.h"

static int	open_file(t_data *data, char *filename, int type,int *quote)
{
	int	fd;

	fd = -2;
	if (type == INPUT)
		fd = open(filename, O_RDONLY, 0644);
	else if (type == HEREDOC)
		fd = handle_heredoc(data, filename,quote);
	else if (type == TRUNC)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (type != HEREDOC && fd < 0)
		perror(filename);
	return (fd);
}
static bool	get_here(t_data *data, t_token *tmp, t_cmd *cmd)
{
	if (tmp->type == HEREDOC)
	{
		// printf("cmd->here_doc = %d\n",cmd->here_doc);
		if (cmd->here_doc >= 0)
			close(cmd->here_doc);
		if (tmp == tmp->next || tmp->next->type <= 5 || tmp->next == data->token)
			return (print_error_token(tmp, data));
		cmd->here_doc = open_file(data, tmp->next->str, HEREDOC,&tmp->next->quote);
		if (cmd->here_doc == -1)
			return (false);
	}
	return (true);
}

bool	get_here_doc(t_data *data, t_token *token, t_cmd *cmd)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->type != PIPE && !get_here(data, tmp, cmd))
		return (false);
	if (tmp->type == PIPE)
		return (true);
	tmp = tmp->next;
	while (tmp->type != PIPE && tmp != data->token)
	{
		if (!get_here(data, tmp, cmd))
			return (false);
		tmp = tmp->next;
	}
	return (true);
}
static bool	get_in(t_data *data, t_token *tmp, t_cmd *cmd)
{
	if (tmp->type == INPUT)
	{
		if (cmd->input_fd >= 0)
			close(cmd->input_fd);
		if (tmp == tmp->next || tmp->next->type <= 5 || tmp->next == data->token)
			return (print_error_token(tmp, data));
		cmd->input_fd = open_file(data, tmp->next->str, INPUT,&tmp->next->quote);
		if (cmd->input_fd == -1)
			return (false);
	}
	else if (tmp->type == HEREDOC)
	{
		cmd->input_fd = cmd->here_doc;
		if (cmd->input_fd == -1)
			return (false);
	}
	return (true);
}

bool	get_infile(t_data *data, t_token *token, t_cmd *cmd)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->type != PIPE && !get_in(data, tmp, cmd))
		return (false);
	if (tmp->type == PIPE)
		return (true);
	tmp = tmp->next;
	while (tmp->type != PIPE && tmp != data->token)
	{
		if (!get_in(data, tmp, cmd))
			return (false);
		tmp = tmp->next;
	}
	return (true);
}

static bool	get_out(t_token *tmp, t_cmd *cmd, t_data *data)
{
	if (tmp->type == TRUNC)
	{
		if (cmd->output_fd >= 0)
			close(cmd->output_fd);
		if (tmp == tmp->next || tmp->next->type <= 5 || tmp->next == data->token)
			return (print_error_token(tmp, data));
		cmd->output_fd = open_file(data, tmp->next->str, TRUNC,&tmp->next->quote);
		if (cmd->output_fd == -1)
			return (false);
	}
	else if (tmp->type == APPEND)
	{
		if (cmd->output_fd >= 0)
			close(cmd->output_fd);
		if (tmp == tmp->next || tmp->next->type <= 5 || tmp->next == data->token)
			return (print_error_token(tmp, data));
		cmd->output_fd = open_file(data, tmp->next->str, APPEND,&tmp->next->quote);
		if (cmd->output_fd == -1)
			return (false);
	}
	return (true);
}

bool	get_outfile(t_token *token, t_cmd *cmd, t_data *data)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->type != PIPE && !get_out(tmp, cmd, data) && !signal_received)
		return (false);
	tmp = tmp->next;
	while (tmp != data->token && tmp->type != PIPE && !signal_received)
	{
		if (!get_out(tmp, cmd, data))
			return (false);
		tmp = tmp->next;
	}
	return (true);
}
