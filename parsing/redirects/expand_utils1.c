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

int valid_dollar(char *heredoc_input, int *i)
{
	if ((heredoc_input[*i + 1] >= 'a' && heredoc_input[*i + 1] <= 'z')
		|| (heredoc_input[*i + 1] >= 'A' && heredoc_input[*i + 1] <= 'Z')
		|| (heredoc_input[*i + 1] == '_'))
		return(1);
	return(0);
}

int	key_len(char *heredoc_input, int *i)
{
	int len = 0;
	int j = *i;
	while ((heredoc_input[j] >= 'a' && heredoc_input[j] <= 'z')
		|| (heredoc_input[j] >= 'A' && heredoc_input[j] <= 'Z')
		|| (heredoc_input[j] >= '0' && heredoc_input[j] <= '9')
		|| (heredoc_input[j] == '_'))
	{
		j++;
		len++;
	}
	return (len);
}

int	values_len(char **values)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (values[i])
	{
		len += ft_strlen(values[i]);
		i++;
	}
	return (len);
}
