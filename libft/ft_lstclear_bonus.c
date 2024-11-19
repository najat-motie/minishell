/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:42:03 by nmotie-           #+#    #+#             */
/*   Updated: 2024/02/17 15:06:34 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*node_next;

	if (lst == NULL || *lst == NULL)
	{
		return ;
	}
	node = *lst;
	while (node != NULL)
	{
		node_next = node->next;
		del(node->content);
		free(node);
		node = node_next;
	}
	*lst = NULL;
}
