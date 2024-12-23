/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ner-roui <ner-roui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 02:09:38 by ner-roui          #+#    #+#             */
/*   Updated: 2024/12/23 16:05:12 by ner-roui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	in_env(t_data *data, char *line, int size, char **str)
{
	char	*tmp;
	char	*key;
	char	*value;

	key = get_dollar_word(line, size);
	value = get_elem_env(data->env_lst, key);
	if (key)
		free(key);
	tmp = ft_strjoin(*str, value);
	if (value)
		free(value);
	free(*str);
	if (!tmp)
		return (0);
	*str = tmp;
	return (1);
}

static int	dollar_point_interrogation(t_data *data, char **str)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_itoa(data->exit_status);
	if (!tmp)
		return (0);
	tmp2 = ft_strjoin(*str, tmp);
	free(tmp);
	free(*str);
	if (!tmp2)
		return (0);
	*str = tmp2;
	return (1);
}

int	add_dollar(char *line, int *index, char **str, t_data *data)
{
	int		ctrl;
	int		n;

	quoting(&data->dq, &data->sq, line[*index]);
	n = *index;
	ctrl = exist_in_env(line, index, data);
	if (ctrl == 1)
		return (in_env(data, &line[n], *index - n - 1, str));
	else if (ctrl == 2)
	{
		(*index) += 2;
		return (dollar_point_interrogation(data, str));
	}
	else
	{
		++(*index);
		while (line[*index] && \
			(ft_isalnum(line[*index]) || line[*index] == '_'))
			++(*index);
		return (1);
	}
}

int	add_char(char *c, char **str, t_data *data, int *index)
{
	char	char_to_str[2];
	char	*tmp2;
	int		i;

	quoting(&data->dq, &data->sq, *c);
	i = 0;
	if (c[i] == '$' && !data->sq && exist_in_env(c, &i, data))
		return (1);
	char_to_str[0] = *c;
	char_to_str[1] = '\0';
	(*index)++;
	tmp2 = ft_strjoin(*str, char_to_str);
	free(*str);
	if (!tmp2)
		return (0);
	*str = tmp2;
	return (1);
}
