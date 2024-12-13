#include "../../minishell.h"

static int	ft_search(char *value, char c)
{
	int	i;

	i = -1;
	while (value[++i])
		if (value[i] == c)
			return (i);
	return (0);
}

static int	end_word(char *value, char *env_lst)
{
	int	i;

	i = 0;
	while (value[i] && (ft_isalnum(value[i]) || value[i] == '_'))
		++i;
	if (i == ft_search(env_lst, '='))
		return (i);
	return (0);
}

/* return 1 si $VAR dans env_lst sinon 0 */
int	exist_in_env(char *line, int *i, t_data *data)
{
	t_env	*tmp;
	int		len;

	if (line[*i + 1] == '?' || line[*i + 1] == '$')
		return (2);
	tmp = data->env_lst;
	// printf("--->%s\n", tmp->key);
	len = len_list(tmp);
	while (len--)
	{
		if (ft_strncmp(tmp->value, &line[*i + 1], \
			end_word(&line[*i + 1], tmp->value)) == 0)
		{
			*i += ft_strlen(tmp->value) - \
				ft_strlen(ft_strchr(tmp->value, '=')) + 1;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

char	*get_elem_env(t_env *env_lst, char *key)
{
	t_env	*tmp;
	int		len;
	int		t;

	if (!key)
		return (NULL);
	tmp = env_lst;
	len = len_list(tmp);
	t = ft_strlen(key);
	while (len--)
	{
		if (ft_strncmp(tmp->value, key, t) == 0)
		{
			len = 0;
			while (tmp->value[len])
				if (tmp->value[len++] == '=')
					break ;
			return (ft_strdup(&(tmp->value[len])));
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_dollar_word(char *line, int size)
{
	char	*dollar;
	int		i;

	dollar = malloc(sizeof(char) * size);
	if (!dollar)
		return (NULL);
	i = 0;
	while (line[++i] && i < size)
		dollar[i - 1] = line[i];
	dollar[i - 1] = '\0';
	return (dollar);
}
