
#include "../../include/minishell.h"

static int	in_env(t_data *data, char *line, int size, char **str)
{
	char	*tmp;
	char	*key;
	char	*value;

	key = get_dollar_word(line, size);
	value = get_elem_env(data->env, key);
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

int	add_dollar(char *line, int *index, char **str, t_data *data)
{
	int		ctrl;
	int		n;

	n = *index;
	ctrl = exist_in_env(line, index, data);
	if (ctrl == 1)
		return (in_env(data, &line[n], *index - n, str));
	else
	{
		++(*index);
		while (line[*index] && \
			(ft_isalnum(line[*index]) || line[*index] == '_'))
			++(*index);
		return (1);
	}
}

int	add_char(char *c, char **str, int *index)
{
	char	char_to_str[2];
	char	*tmp2;
	int		i;

	i = 0;
	
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

int	replace_dollar(char **line, t_data *data)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strdup("");
	while ((*line)[i])
	{
		if((*line)[i] == '$' && (*line)[i - 1] == '\'')
			i++;
		if ((*line)[i] && (*line)[i + 1] && (*line)[i] == '$' && (*line)[i - 1] != '\'') 
		{
			if ((*line)[i] && (*line)[i + 1] && (*line)[i] == '$' && \
			((*line)[i + 1] != '\'' && (*line)[i + 1] != '"') && \
			(ft_isalpha((*line)[i + 1]) ||(*line)[i + 1] == '_') )
			{
				printf("data - > %d\n", data->sq);
				if(!add_dollar((*line), &i, &str, data))
				return (0);
			}
		}
		if ((*line)[i] && !add_char(&(*line)[i], &str,&i))
			return (0);
	}
	free(*line);
	*line = str;
	return (1);
}
