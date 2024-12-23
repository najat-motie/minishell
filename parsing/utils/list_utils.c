/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ner-roui <ner-roui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:03:44 by ner-roui          #+#    #+#             */
/*   Updated: 2024/12/23 16:50:56 by ner-roui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

size_t	len_list(t_env *list)
{
	t_env	*tmp;
	size_t	i;

	i = 0;
	tmp = list;
	if (tmp)
	{
		while (tmp)
		{
			++i;
			tmp = tmp->next;
		}
		return (i);
	}
	return (0);
}
