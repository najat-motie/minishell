#include "../../minishell.h"

void	quoting(bool *dq, bool *sq, char c)
{
	if ((c == '\'' || c == '"') && !*sq && !*dq)
	{
		if (c == '\'' && !*dq)
			*sq = true;
		else if (c == '"' && !*sq)
			*dq = true; //1
		// if (index)
		// 	++(*index);
	}
	else if ((c == '\'' || c == '"'))
	{
		if (c == '\'' && !*dq && *sq)
			*sq = false;
		else if (c == '"' && !*sq && *dq)
			*dq = false;
		// if (index)
		// 	++(*index);
	}
}

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
	// printf("tmp = %s\n", tmp);
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
	printf("exit status = %s\n", tmp);
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

	quoting(&data->dq, &data->sq,line[*index]);
	n = *index;

	// printf("line[*index]_0 = %c\n", line[*index]);
	ctrl = exist_in_env(line, index, data);
	// printf("line[*index]_1 = %c\n", line[*index]);
	// printf("*index - n = %d\n", *index - n);
	if (ctrl == 1)
		return (in_env(data, &line[n], *index - n - 1 , str));
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

	// printf("c = %c\n", *c);
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

int	replace_dollar(char **line, t_data *data)
{
	int		i;
	char	*str;
	// bool	sq1 = false;
	i = 0;
	data->sq = false;
	data->dq = false;
	str = ft_strdup("");
	while ((*line)[i])
	{
		// quoting(&data->dq, &data->sq,(*line)[i]);
		// quoting(&sq1, (*line)[i]);
		// printf("str = %s | sq = %d  | dq = %d\n ", str,data->sq,data->dq);
		if ((*line)[i] && (*line)[i + 1] && (*line)[i] == '$' && \
			((*line)[i + 1] != '\'' && (*line)[i + 1] != '"') && \
			(ft_isalpha((*line)[i + 1]) || (*line)[i + 1] == '?' || \
			(*line)[i + 1] == '_') && !data->sq && !add_dollar((*line), &i, &str, data))
			return (0);
		if ((*line)[i] && !add_char(&(*line)[i], &str, data, &i))
			return (0);

	}
	// free(*line);
	*line = str;
	// printf("line = %s\n", *line);
	return (1);
}
