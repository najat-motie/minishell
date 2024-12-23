/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ner-roui <ner-roui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:33:28 by ner-roui          #+#    #+#             */
/*   Updated: 2024/12/23 16:02:02 by ner-roui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *replace_dollar(char **line, t_data *data)
{
	int		i;
	char	*str;

	i = 0;
	data->sq = false;
	data->dq = false;
	str = ft_strdup("");
	while ((*line)[i])
	{
		if ((*line)[i] && (*line)[i + 1] && (*line)[i] == '$' && \
			((*line)[i + 1] != '\'' && (*line)[i + 1] != '"') && \
			(ft_isalpha((*line)[i + 1]) || (*line)[i + 1] == '?' || \
			(*line)[i + 1] == '_') && !data->sq && \
			!add_dollar((*line), &i, &str, data))
			return (NULL);
        if	((*line)[i] == '$' && ((*line)[i + 1] == '\'' || \
			(*line)[i + 1] == '"'))
			i++;
		if ((*line)[i] && !add_char(&(*line)[i], &str, data, &i))
			return (NULL);

	}
	return (str);
}