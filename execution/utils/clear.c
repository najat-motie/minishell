/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:22:33 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/14 16:22:34 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	clear_env(t_env **lst)
{
	t_env	*node;
	t_env	*save_next;

	if (lst == NULL || *lst == NULL)
		return ;
	node = *lst;
	while (node != NULL)
	{
		save_next = node->next;
		free(node->key);
		free(node->value);
		free(node->str);
		free(node);
		node = save_next;
	}
	*lst = NULL;
}
