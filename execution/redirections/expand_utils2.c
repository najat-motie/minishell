#include "../../minishell.h"

char	*get_keyname(char *heredoc_input, int *removed_count, int *i)
{
	int		j;
	int		k;
	char	*to_expand;

	j = 0;
	k = key_len(heredoc_input, i);
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
		to_expand[j++] = heredoc_input[(*i)++];
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

void	init_vars(int *i, int *j, int *n)
{
	*i = 0;
	*j = 0;
	*n = 0;
}

void	replace_key_by_value(char *array, int *j, char **values, int *n)
{
	int m = 0;
	while (values[*n] && values[*n][m])
		array[(*j)++] = values[*n][m++];
}
