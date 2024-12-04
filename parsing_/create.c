#include "../minishell.h"

t_red	*ft_new_red(char *type, char *file, int not_quouted)
{
	t_red	*node;

	node = malloc(sizeof(t_red));
	if (node == NULL)
		return (NULL);
	node->symbol_type = type;
	node->file_name = file;
	node->not_quouted = not_quouted;
	
	node->next = NULL;
	return (node);
}

void	add_back_red(t_red **lst, t_red *new)
{
	t_red	*node;
	
	if (*lst == NULL)
		*lst = new;
	else
	{
		node = *lst;
		while (node->next != NULL)
			node = node->next;
		node->next = new;
	}
}

void    fill_redicts_lst(char *commands, t_red **red_lst)
{
	// red_lst = NULL;
	int not_quouted = 1;
	char **cmnds = ft_split(commands, ' ');
	char **files = get_files(cmnds, &not_quouted);
	char **types = get_types(cmnds);
	int i = 0;
	while(types[i] && files[i])
	{
    	add_back_red(red_lst, ft_new_red(types[i], files[i], not_quouted));
		i++;
	}
	ft_free(cmnds);
}

// void    fill_redicts_lst(t_red **red_lst)
// {
//     add_back_red(red_lst, ft_new_red("<<", "a", 0));
//     add_back_red(red_lst, ft_new_red("<<", "b", 0));
//     // add_back_red(red_lst, ft_new_red("<<", "file3", 0));
//     // add_back_red(red_lst, ft_new_red("<<", "file4", 0));
// }

t_cmd	*ft_newcmd(char *commands)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (node == NULL)
		return (NULL);

    char **cmnds = ft_split(commands, ' ');

    node->input_fd = -1;
    node->output_fd = -1;
    node->heredoc_fd = -1;

    // char *options[] = {NULL};
    // // char *options[] = {"-l", "-a", NULL};
	// node->options = options;

	node->commands = get_commands(cmnds);

	// node->red_lst = NULL;
	// fill_redicts_lst(&node->red_lst);

	t_red *red_lst = NULL;
	fill_redicts_lst(commands, &red_lst);
	node->red_lst = red_lst;

	node->next = NULL;
	free(commands);
;	return (node);
}

void	add_back_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*node;
	
	if (*lst == NULL)
		*lst = new;
	else
	{
		node = *lst;
		while (node->next != NULL)
			node = node->next;
		node->next = new;
	}
}

void    fill_cmd_lst(t_data *data)
{
    int i = 0;
	data->cmd_lst = NULL;
    char **commands = ft_split(data->input, '|');

    while(commands && commands[i])
    {
        add_back_cmd(&data->cmd_lst, ft_newcmd(commands[i]));
        i++;
    }
	// ft_free(commands);
	// | without its two commands
	// > >> < << without file
	// 	---> syntax error
}
