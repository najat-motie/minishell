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
			if ((heredoc_input[i + 1] >= 'a' && heredoc_input[i + 1] <= 'z')
				|| (heredoc_input[i + 1] >= 'A' && heredoc_input[i + 1] <= 'Z')
				|| (heredoc_input[i + 1] == '_'))
			{
				i++;
				(*removed_count)++;
				to_expand = get_keyname(heredoc_input, removed_count, &i);
				values[j++] = retreive_value(data, to_expand);
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
	char **values_;

	removed_count = 0;
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
	int		m;

	i = 0;
	j = 0;
	n = 0;
	m = 0;
	while (heredoc_input[i])
	{
		while (heredoc_input[i] && heredoc_input[i] != '$')
			array[j++] = heredoc_input[i++];
		if (heredoc_input[i] == '$')
		{
			if ((heredoc_input[i + 1] >= 'a' && heredoc_input[i + 1] <= 'z')
				|| (heredoc_input[i + 1] >= 'A' && heredoc_input[i + 1] <= 'Z')
				|| (heredoc_input[i + 1] == '_'))
			{
				i++;
				m = 0;
				while (values[n] && values[n][m])
					array[j++] = values[n][m++];
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
	char *array;
	int		count;
	int		len;
	char	**values;

	count = 0;
	values = extract_values(data, heredoc_input, &count);
	len = values_len(values);
	array = malloc(ft_strlen(heredoc_input) - count + len + 1);
	if (!array)
	{
		perror("malloc");
		return (NULL);
	}
	input = fill_input(heredoc_input, values, array);
	return (input);
}
