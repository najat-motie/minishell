/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ner-roui <ner-roui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:34:55 by ner-roui          #+#    #+#             */
/*   Updated: 2024/12/23 16:51:53 by ner-roui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_true_lst_cmd(t_data *data)
{
	if (!data->token || !create_list_cmd(data))
	{
		free_token(&data->token);
		free_cmd(&data->cmd_lst);
		return (false);
	}
	return (true);
}

bool	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (line[i] == '\0')
	{
		free(line);
		return (true);
	}
	return (false);
}

bool	parseline(t_data *data, char *line)
{
	char	*str;

	if (open_quote(data, line))
	{
		free(line);
		return (false);
	}
	str = replace_dollar(&line, data);
	if (!str || !create_list_token(&data->token, str))
	{
		printf("Error: malloc failed\n");
		free(str);
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	}
	free(str);
	if (data->token && data->token->prev->type == PIPE)
	{
		write(2, "Error: Unclosed pipe\n", 21);
		data->exit_status = 2;
		free_token(&data->token);
		return (false);
	}
	if (!is_true_lst_cmd(data))
		return (false);
	return (check_pipe(data));
}
