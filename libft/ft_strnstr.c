/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:28:14 by nmotie-           #+#    #+#             */
/*   Updated: 2024/02/15 13:28:26 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	index;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0')
	{
		if (haystack[i] == needle[0])
		{
			index = 0;
			j = 0;
			while ((haystack[i + index] == needle[j]) && i + index < len)
			{
				index++;
				j++;
				if (needle[j] == '\0') 
					return ((char *)&haystack[i]);
			}
		}
		i++;
	}
	return (NULL);
}
