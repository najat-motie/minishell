/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 22:33:21 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/24 15:12:13 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**fill_values(t_data data, char *heredoc_input, char **values,
		int *removed_count)
{
	int		i;
	int		j;
	char	*to_expand;

	i = 0;
	j = 0;
	while (heredoc_input[i])
	{
		if (heredoc_input[i] == '$')
		{
			if (valid_dollar(heredoc_input, &i))
			{
				i++;
				(*removed_count)++;
				to_expand = get_keyname(heredoc_input, removed_count, &i);
				values[j++] = ft_strdup(retreive_value(data, to_expand));
				free(to_expand);
			}
		}
		i++;
	}
	values[j] = NULL;
	return (values);
}

char	**extract_values(t_data data, char *heredoc_input, int *removed_count)
{
	int		dollar_nb;
	char	**values;

	dollar_nb = dollar_count(heredoc_input);
	values = malloc((dollar_nb + 1) * sizeof(char *));
	if (values == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	values = fill_values(data, heredoc_input, values, removed_count);
	return (values);
}

char	*fill_input(char *heredoc_input, char **values, char *array)
{
	int	i;
	int	j;
	int	n;

	init_vars(&i, &j, &n);
	while (heredoc_input[i])
	{
		while (heredoc_input[i] && heredoc_input[i] != '$')
			array[j++] = heredoc_input[i++];
		if (heredoc_input[i] == '$')
		{
			if (valid_dollar(heredoc_input, &i))
			{
				i++;
				replace_key_by_value(array, &j, values, &n);
				skip_key(heredoc_input, &i);
				n++;
			}
			else
				array[j++] = heredoc_input[i++];
		}
	}
	array[j] = '\0';
	return (array);
}

char	*expand_input(t_data data, char *heredoc_input)
{
	char	*new_input;
	int		removed_count;
	int		len_values;
	char	**values;

	removed_count = 0;
	values = extract_values(data, heredoc_input, &removed_count);
	len_values = values_len(values);
	new_input = malloc(ft_strlen(heredoc_input) - removed_count + len_values
			+ 1);
	if (!new_input)
	{
		perror("malloc");
		return (NULL);
	}
	new_input = fill_input(heredoc_input, values, new_input);
	ft_free(values);
	return (new_input);
}
