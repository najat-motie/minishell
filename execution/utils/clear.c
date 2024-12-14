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
