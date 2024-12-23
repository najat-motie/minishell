/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_here_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ner-roui <ner-roui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 01:52:10 by ner-roui          #+#    #+#             */
/*   Updated: 2024/12/23 15:28:23 by ner-roui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	get_here(t_data *data, t_token *tmp, t_cmd *cmd)
{
	if (tmp->type == HEREDOC)
	{
		if (cmd->here_doc >= 0)
			close(cmd->here_doc);
		if (tmp == tmp->next || tmp->next->type <= 5 || \
		tmp->next == data->token)
			return (print_error_token(tmp, data));
		cmd->here_doc = open_file(data, tmp->next->str, HEREDOC, \
		tmp->next->quote);
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