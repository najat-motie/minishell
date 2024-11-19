/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:28:37 by nmotie-           #+#    #+#             */
/*   Updated: 2024/02/15 13:30:03 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substring;

	if (s == NULL)
		return (NULL);
	i = 0;
	if (start > ft_strlen(s))
		substring = (char *)malloc(1);
	else if (len > ft_strlen(s) - start)
		substring = (char *)malloc(ft_strlen(s) - start + 1);
	else
		substring = (char *)malloc(len + 1);
	if (substring == NULL)
		return (NULL);
	if (start < ft_strlen(s))
	{
		while (s[start + i] && i < len)
		{
			substring[i] = s[start + i];
			i++;
		}
	}
	substring[i] = '\0';
	return (substring);
}
