/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 18:58:42 by ner-roui          #+#    #+#             */
/*   Updated: 2024/12/14 12:01:49 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_memory(char **result, int j)
{
	while (j >= 0)
	{
		if (result[j] != NULL)
			free(result[j]);
		j--;
	}
	free(result);
	result = NULL;
}

static int	count_words(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static char	*fill_word(char *s, int start, int end)
{
	int		i;
	char	*array;

	i = 0;
	array = malloc(sizeof(char) * (end - start + 1));
	if (array == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	while (start < end)
	{
		array[i] = s[start];
		i++;
		start++;
	}
	array[i] = '\0';
	return (array);
}

static void	fill_array(char *s, char c, int words, char **array)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	start = 0;
	while (j < words)
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		array[j] = fill_word(s, start, i);
		if (array[j] == NULL)
		{
			free_memory(array, j);
			return ;
		}
		j++;
	}
	array[j] = NULL;
}

char	**ft_split(char *s, char c)
{
	int		words;
	char	**array;

	words = count_words(s, c);
	array = malloc(sizeof(char *) * (words + 1));
	if (array == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	fill_array(s, c, words, array);
	return (array);
}
