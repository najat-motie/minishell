#include "../minishell.h"

char **get_commands(char **str)
{
    int i = 0;
	int j = 0;
	int k = 0;
	while(str[i] && (ft_strcmp(str[i], ">") != 0 && ft_strcmp(str[i], ">>") != 0 
        && ft_strcmp(str[i], "<") != 0 && ft_strcmp(str[i], "<<") != 0))
	{
		i++;
		j++;
	}
    char **commands = malloc((j + 1) * sizeof(char *));
	i = 0;
    while (k < j)
        commands[k++] = str[i++];
    commands[k] = NULL;
    return(commands);
}

int number_redirects(char **command)
{
	int count = 0;
	int i = 0;
	while(command[i])
	{
		if(ft_strcmp(command[i], ">") == 0 || ft_strcmp(command[i], ">>") == 0 || ft_strcmp(command[i], "<") == 0 || ft_strcmp(command[i], "<<") == 0)
			count++;
		i++;
	}
	return(count);
}

char **get_types(char **cmnds)
{
	int i = 0;
	int count = number_redirects(cmnds);
	char **all_types = malloc((count + 1) * sizeof(char *));
	int j = 0;
	while(cmnds[i])
	{
		if(ft_strcmp(cmnds[i], "<") == 0 || ft_strcmp(cmnds[i], "<<") == 0 
			|| ft_strcmp(cmnds[i], ">") == 0 || ft_strcmp(cmnds[i], ">>") == 0)
		{
			int k = 0;
			while(cmnds[i][k] != ' ' && cmnds[i][k] != '\0')
				k++;
			all_types[j] = malloc(k + 1);
			k = 0;
			while(cmnds[i][k])
			{
				all_types[j][k] = cmnds[i][k];
				k++;
			}
			all_types[j][k] = '\0';
			j++;
		}
		i++;
	}
	all_types[j] = NULL;
	return(all_types);
}


char **get_files(char **cmnds, int *not_quouted)
{
	int i = 0;
	int count = number_redirects(cmnds);
	char **all_files = malloc((count + 1) * sizeof(char *));
	int l = 0;
	while(cmnds[i])
	{
		if(ft_strcmp(cmnds[i], "<") == 0 || ft_strcmp(cmnds[i], "<<") == 0 
			|| ft_strcmp(cmnds[i], ">") == 0 || ft_strcmp(cmnds[i], ">>") == 0)
		{
			if(ft_strcmp(cmnds[i], "<<") == 0)
			{
				int x = i;
				int y = 0;
				x++;
				if(cmnds[x][y] == '"' || cmnds[x][y] == '\'')
				{
					y++;
					while(cmnds[x][y] != '"' && cmnds[x][y] == '\'' && cmnds[x][y] != '\0')
						y++;
					if(cmnds[x][y] == '"' || cmnds[x][y] == '\'')
						*not_quouted = 0;
				}
			}
			int j = i;
			j++;
			int k = 0;
			while(cmnds[j][k] != ' ' && cmnds[j][k])
				k++;
			all_files[l] = malloc(k + 1);
			k = 0;
			while(cmnds[j][k])
			{
				all_files[l][k] = cmnds[j][k];
				k++;
			}
			all_files[l][k] = '\0';
			l++;
		}
		i++;
	}
	all_files[l] = NULL;
	return(all_files);
}

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

	char **options = get_commands(cmnds);
	node->commands = options;

	// node->red_lst = NULL;
	// fill_redicts_lst(&node->red_lst);

	t_red *red_lst = NULL;
	fill_redicts_lst(commands, &red_lst);
	node->red_lst = red_lst;

	node->next = NULL;
	return (node);
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
	
	// | without its two commands
	// > without file
	// 	---> syntax error
}
