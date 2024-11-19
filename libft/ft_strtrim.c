/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:28:25 by nmotie-           #+#    #+#             */
/*   Updated: 2024/02/15 13:29:46 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_set(char s, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	len_s1;
	char	*trimmed_str;
	size_t	i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	len_s1 = ft_strlen(s1);
	while (start < len_s1 && find_set(s1[start], set) == 1)
		start++;
	while (len_s1 && len_s1 - 1 > start && find_set(s1[len_s1 - 1], set) == 1)
		len_s1--;
	trimmed_str = (char *)malloc(len_s1 - start + 1);
	if (trimmed_str == NULL)
		return (NULL);
	i = 0;
	while (s1[start + i] && i < len_s1 - start)
	{
		trimmed_str[i] = s1[start + i];
		i++;
	}
	trimmed_str[i] = '\0';
	return (trimmed_str);
}
