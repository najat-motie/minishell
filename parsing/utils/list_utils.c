#include "../../minishell.h"

int	free_list(t_env **list)
{
	t_env	*tmp;
	t_env	*current;

	if (!(*list))
		return (0);
	current = *list;
	while (current->next != *list)
	{
		tmp = current;
		current = current->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	free(current->key);
	free(current->value);
	free(current);
	*list = NULL;
	return (0);
}

// static int	list_new_elem_str(t_env **new, char *elem)
// {
// 	(*new) = malloc(sizeof(t_env));
// 	if (*new == NULL)
// 		return (0);
// 	(*new)->str = elem;
// 	(*new)->next = NULL;
// 	(*new)->prev = NULL;
// 	return (1);
// }

// static void	add_first(t_env **list, t_env *new)
// {
// 	(*list) = new;
// 	(*list)->prev = *list;
// 	(*list)->next = *list;
// }

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

// int	append(t_env **list, char *elem)
// {
// 	t_env	*new;

// 	if (!list_new_elem_str(&new, elem))
// 		return (0);
// 	if (!(*list))
// 		add_first(list, new);
// 	else
// 	{
// 		new->prev = (*list)->prev;
// 		new->next = (*list);
// 		(*list)->prev->next = new;
// 		(*list)->prev = new;
// 	}
// 	return (1);
// }
