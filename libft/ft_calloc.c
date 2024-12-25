/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:56:44 by ner-roui          #+#    #+#             */
/*   Updated: 2024/12/24 12:29:46 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*dest;

	if ((int)count < 0 || (int)size < 0)
		return (NULL);
	dest = (void *)malloc (count * size);
	if (dest == NULL)
		return (NULL);
	ft_bzero(dest, count * size);
	return (dest);
}
