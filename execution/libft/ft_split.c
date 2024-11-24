/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:32:24 by nmotie-           #+#    #+#             */
/*   Updated: 2024/11/24 14:19:15 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*free_memory(char **result, int j)
{
	while (j >= 0)
	{
		if (result[j] != NULL)
			free(result[j]);
		j--;
	}
	free(result);
	return (NULL);
}

int	count_words(char *s, char c)
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

char *fill_word(char *s, int start, int end)
{
	int i = 0;
	char *array = malloc(sizeof(char) * (end - start + 1));
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
	return(array);
}

char **fill_array(char *s, char c, int words)
{
	int i = 0;
    int j = 0;
    int start = 0;
	
	char **array = malloc(sizeof(char *) * (words + 1));
    if (array == NULL)
	{
		perror("malloc");
        return (NULL);
	}
    while (j < words)
    {
       while (s[i] && s[i] == c)
            i++;
        start = i;
        while (s[i] && s[i] != c)
            i++;
        array[j] = fill_word(s, start, i);
        if (array[j] == NULL)
            return (free_memory(array, j));
        j++;
    }
    array[j] = NULL;
	return (array);
}

char **ft_split(char *s, char c)
{
    int words;
    char **array;

    words = count_words(s, c);
    array = fill_array(s, c, words);
	if(array)
		return(array);
    return(NULL);
}
