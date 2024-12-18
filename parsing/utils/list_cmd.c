#include "../../minishell.h"

static int	cmd_new_elem(t_cmd **new, int input_fd, int output_fd,int here_doc, char **commands)
{
	(*new) = malloc(sizeof(t_cmd));
	if (*new == NULL)
		return (0);
	(*new)->skip_cmd = false;
	(*new)->input_fd = input_fd;
	(*new)->output_fd = output_fd;
	(*new)->here_doc = here_doc;
	(*new)->commands = commands;
	(*new)->next = NULL;
	(*new)->prev = NULL;
	return (1);
}

int	append_cmd(t_cmd **list, int input_fd, int output_fd,int here_doc, char **commands)
{
	t_cmd	*new;

	if (!cmd_new_elem(&new, input_fd, output_fd, here_doc, commands))
		return (0);
	if (!(*list))
	{
		(*list) = new;
		(*list)->prev = *list;
		(*list)->next = *list;
	}
	else
	{
		new->prev = (*list)->prev;
		new->next = (*list);
		(*list)->prev->next = new;
		(*list)->prev = new;
	}
	return (1);
}

static void	free_all_cmd(t_cmd *tmp)
{
	if (tmp->input_fd > 0)
		close(tmp->input_fd);
	tmp->input_fd = -2;
	if (tmp->output_fd > 0)
		close(tmp->output_fd);
	tmp->output_fd = -2;
	free_array(tmp->commands);
}

void	free_cmd(t_cmd **list)
{
	t_cmd	*tmp;
	t_cmd	*current;

	if (!(*list))
		return ;
	current = *list;
	while (current->next != *list)
	{
		tmp = current;
		current = current->next;
		free_all_cmd(tmp);
		free(tmp);
	}
	free_all_cmd(current);
	free(current);
	*list = NULL;
}

size_t	len_cmd(t_cmd *list)
{
	t_cmd	*tmp;
	size_t	i;

	if ((list))
	{
		tmp = list;
		i = 1;
		while (tmp->next != list)
		{
			++i;
			tmp = tmp->next;
		}
		return (i);
	}
	return (0);
}
