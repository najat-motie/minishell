/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ner-roui <ner-roui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:57:22 by ner-roui          #+#    #+#             */
/*   Updated: 2023/11/12 17:58:13 by ner-roui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	len;
	char	*dst;

	if(!s1)
		return(NULL);
	i = 0;
	len = ft_strlen(s1) + 1;
	dst = (char *)malloc(len);
	if (dst == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	while (s1[i] != '\0')
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

