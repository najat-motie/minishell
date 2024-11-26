#include "../../minishell.h"

int	dollar_count(char *heredoc_input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (heredoc_input[i])
	{
		if (heredoc_input[i] == '$' && ((heredoc_input[i + 1] >= 'a'
					&& heredoc_input[i + 1] <= 'z') || (heredoc_input[i
					+ 1] >= 'A' && heredoc_input[i + 1] <= 'Z')
				|| (heredoc_input[i + 1] == '_')))
			count++;
		i++;
	}
	return (count);
}

int	key_len(char *heredoc_input)
{
	int	i;

	i = 0;
	while ((heredoc_input[i] >= 'a' && heredoc_input[i] <= 'z')
		|| (heredoc_input[i] >= 'A' && heredoc_input[i] <= 'Z')
		|| (heredoc_input[i] >= '0' && heredoc_input[i] <= '9')
		|| (heredoc_input[i] == '_'))
		i++;
	return (i);
}

int	values_len(char **values)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (values[i])
	{
		i++;
		len += ft_strlen(values[i]);
	}
	return (len);
}

char	*get_keyname(char *heredoc_input, int *removed_count, int *i)
{
	int		j;
	int		k;
	char	*to_expand;

	j = 0;
	k = key_len(heredoc_input);
	to_expand = malloc(k + 1);
	if (to_expand == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	while ((heredoc_input[*i] >= 'a' && heredoc_input[*i] <= 'z')
		|| (heredoc_input[*i] >= 'A' && heredoc_input[*i] <= 'Z')
		|| (heredoc_input[*i] >= '0' && heredoc_input[*i] <= '9')
		|| (heredoc_input[*i] == '_'))
	{
		to_expand[j++] = heredoc_input[*i++];
		(*removed_count)++;
	}
	(*i)--;
	to_expand[j] = '\0';
	return (to_expand);
}

void	skip_key(char *heredoc_input, int *i)
{
	while ((heredoc_input[*i] >= 'a' && heredoc_input[*i] <= 'z')
		|| (heredoc_input[*i] >= 'A' && heredoc_input[*i] <= 'Z')
		|| (heredoc_input[*i] >= '0' && heredoc_input[*i] <= '9')
		|| (heredoc_input[*i] == '_'))
		(*i)++;
}
