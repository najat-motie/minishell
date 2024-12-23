/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ner-roui <ner-roui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 01:50:56 by ner-roui          #+#    #+#             */
/*   Updated: 2024/12/23 15:20:24 by ner-roui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	quoting(bool *dq, bool *sq, char c)
{
	if ((c == '\'' || c == '"') && !*sq && !*dq)
	{
		if (c == '\'' && !*dq)
			*sq = true;
		else if (c == '"' && !*sq)
			*dq = true;
	}
	else if ((c == '\'' || c == '"'))
	{
		if (c == '\'' && !*dq && *sq)
			*sq = false;
		else if (c == '"' && !*sq && *dq)
			*dq = false;
	}
}

void	quoting_choice(bool *dq, bool *sq, int *index, char c)
{
	if ((c == '\'' || c == '"') && !*sq && !*dq)
	{
		if (c == '\'' && !*dq)
			*sq = true;
		else if (c == '"' && !*sq)
			*dq = true; 
		if (index)
			++(*index);
	}
	else if ((c == '\'' || c == '"'))
	{
		if (c == '\'' && !*dq && *sq)
			*sq = false;
		else if (c == '"' && !*sq && *dq)
			*dq = false;
		if (index)
			++(*index);
	}
}

int	open_quote(t_data *data, char *line)
{
	bool	dq;
	bool	sq;
	int		i;

	i = 0;
	dq = false;
	sq = false;
	while (line && line[i])
	{
		quoting_choice(&dq, &sq, &i, line[i]);
		if (line[i] && line[i] != '\'' && line[i] != '"')
			++i;
	}
	if (dq || sq)
	{
		print_error("open quote\n");
		data->exit_status = 2;
		return (1);
	}
	return (0);
}
