#include "../../minishell.h"

char **fill_values(t_data data, char *heredoc_input, char **values, int *removed_count)
{
	int		i = 0;
	int		j = 0;
	char	*to_expand;
	while (heredoc_input[i])
	{
		if (heredoc_input[i] == '$')
		{
			if (valid_dollar(heredoc_input, &i))
			{
				i++;
				(*removed_count)++;
				to_expand = get_keyname(heredoc_input, removed_count, &i);
				values[j++] = retreive_value(data, to_expand);
				free(to_expand);
			}
		}
		i++;
	}
	values[j] = NULL;
	return(values);
}

char	**extract_values(t_data data, char *heredoc_input, int *removed_count)
{
	int		dollar;
	char	**values;
	char 	**values_;

	dollar = dollar_count(heredoc_input);
	values = malloc((dollar + 1) * sizeof(char *));
	if (values == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	values_ = fill_values(data, heredoc_input, values, removed_count);
	return(values_);
}

char	*fill_input(char *heredoc_input, char **values, char *array)
{
	int		i;
	int		j;
	int		n;

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
				array[j++] = heredoc_input[i];
		}
	}
	array[j] = '\0';
	return (array);
}

char	*expand_input(t_data data, char *heredoc_input)
{
	char	*input;
	char 	*array;
	int		removed_count;
	int		len;
	char	**values;

	removed_count = 0;
	values = extract_values(data, heredoc_input, &removed_count);
	len = values_len(values);
	array = malloc(ft_strlen(heredoc_input) - removed_count + len + 1);
	if (!array)
	{
		perror("malloc");
		return (NULL);
	}
	input = fill_input(heredoc_input, values, array);
	ft_free(values);
	return (input);
}
