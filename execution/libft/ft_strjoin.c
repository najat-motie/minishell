/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:27:48 by nmotie-           #+#    #+#             */
/*   Updated: 2024/11/24 14:32:03 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *fill_string(char *s1, char *s2, char *new_s)
{
	int	i;
	int	j;
	
	i = 0;
	while (s1[i])
	{
		new_s[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		new_s[i + j] = s2[j];
		j++;
	}
	new_s[i + j] = '\0';
	return (new_s);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new_s;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	new_s = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (new_s == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	new_s = fill_string(s1, s2, new_s);
	return(new_s);
}