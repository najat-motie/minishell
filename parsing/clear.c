#include "../minishell.h"

void	lstclear_env(t_env **lst)
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
		free(node);
		node = save_next;
	}
	*lst = NULL;
}

void	lstclear_red(t_red **lst)
{
	t_red	*node;
	t_red	*save_next;

	if (lst == NULL || *lst == NULL)
		return ;
	node = *lst;
	while (node != NULL)
	{
		save_next = node->next;
		free(node->file_name);
		free(node->symbol_type);
		free(node);
		node = save_next;
	}
	*lst = NULL;
}

void	lstclear_cmd(t_cmd **lst)
{
	t_cmd	*node;
	t_cmd	*save_next;

	if (lst == NULL || *lst == NULL)
		return ;
	node = *lst;
	while (node != NULL)
	{
		save_next = node->next;
		ft_free(node->commands);
        lstclear_red(&node->red_lst);
		node = save_next;
	}
	*lst = NULL;
}