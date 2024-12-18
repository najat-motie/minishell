#include "minishell.h"

// int	make_env(t_data *data, char **envp)
// {
// 	t_env	*list;
// 	int		i;
// 	char	*tmp;

// 	if (!(*envp))
// 		return (0);
// 	i = -1;
// 	list = NULL;
// 	while (envp[++i])
// 	{
// 		tmp = ft_strdup(envp[i]);
// 		if (!tmp)
// 			return (free_list(&list));
// 		if (!append(&list, tmp))
// 			return (free_list(&list));
// 	}
// 	data->env_lst = list;
// 	return (1);
// }
void	print_token(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp->next != token)
	{
		printf("Type : %d, [%s]\n", tmp->type, tmp->str);
		tmp = tmp->next;
	}
	printf("Type : %d, [%s]\n",  tmp->type, tmp->str);
}

void	print_tab(char **tab)
{
	int	i;

	if (!(tab))
	{
		printf("NULL");
		return ;
	}
	i = 0;
	printf("[");
	while (tab[i])
	{
		printf("%s", tab[i]);
		if (tab[i + 1])
			printf(", ");
		i++;
	}
	printf("]");
}

void	print_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp->next != cmd)
	{
		printf("Skip -> %d, infile -> %d, outfile -> %d, cmd : ",
		tmp->skip_cmd, tmp->input_fd, tmp->output_fd);
		print_tab(tmp->commands);
		printf("\n");
		tmp = tmp->next;
	}
	printf("Skip -> %d, infile -> %d, outfile -> %d, cmd : ", tmp->skip_cmd,
		 tmp->input_fd, tmp->output_fd);
	print_tab(tmp->commands);
	printf("\n");
}

void	init_data(t_data *data)
{
	data->token = NULL;
	data->env_lst = NULL;
	data->cmd_lst = NULL;
	data->exit_status = 0;
}

bool	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (line[i] == '\0')
	{
		free(line);
		return (true);
	}
	return (false);
}

bool	parseline(t_data *data, char *line)
{
	if (open_quote(data, line))
	{
		free(line);
		return (false);
	}
	if (!replace_dollar(&line, data) || !create_list_token(&data->token, line))
	{
		printf("Error: malloc failed\n");
		free(line);
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	}
	free(line);
	print_token(data->token);
	if (data->token && data->token->prev->type == PIPE)
	{
		write(2, "Error: Unclosed pipe\n", 21);
		data->exit_status = 2;
		free_token(&data->token);
		return (false);
	}
	if (!data->token || !create_list_cmd(data))
	{
		free_token(&data->token);
		free_cmd(&data->cmd_lst);
		return (false);
	}
    print_cmd(data->cmd_lst);
	return (check_pipe(data));
}

void    ft_free(char **s)
{
    int i = 0;
    while (s[i])
    {
        free(s[i]);
        i++;
    }
    free(s);
}

// void    clear_resources(t_data *data)
// {
    // free(data->line);
    // lstclear_cmd(&data->cmd_lst);
// }

int commands_numbr(t_data data)
{
    int nb = 0;
    t_cmd *tmp = data.cmd_lst;
    if(tmp)
    {
        nb++;
        tmp = tmp->next;
    }
    while(tmp != data.cmd_lst)
    {
        nb++;
        tmp = tmp->next;
    }
    return(nb);
}

// void    handle_input(t_data *data, char *line)
// {
    // t_data	data;

	// atexit(leaks);
	// init_data(&data, argc, argv);

   
    // if(data->line == NULL)
    //     exit(EXIT_SUCCESS);
    // if(*data->line != '\0')
    //     add_history(data->line);
    // data->cmd_nb = commands_numbr(*data);
    // if(data->cmd_lst)
    // {
    //     handle_redirects(data);
    //     if(data->cmd_nb == 1 && builtin_only(data->cmd_lst->commands) && !signal_received)
    //         handle_builtins(data, data->cmd_lst->commands);
    //     else if(!signal_received)
    //         excute_commands(data);
    // }
    // clear_resources(data);
    // system("leaks minishell");
// }

int main(int argc, char **argv, char **envp) 
{
    t_data  data;
	char	*line;
    char    *prompt;

    (void)argc;
    (void)argv;
    prompt = "minishell> ";
    if(signal(SIGQUIT, SIG_IGN) == SIG_ERR)
        perror("signal");
    if(signal(SIGINT, sigint_parent) == SIG_ERR)
        perror("signal");
    init_data(&data);
    make_env(&data, envp);
    // printf("%s\n", data.env_lst->str);
    while (1)
    {
        signal_received = 0;
        line = readline(prompt);
		if (!line)
        {
            clear_env(&data.env_lst);
            exit(EXIT_SUCCESS);
        }
        if(*line != '\0')
            add_history(line);
		if (empty_line(line))
			continue ;
		if (!parseline(&data, line))
			continue ;
		// printf("command[0]-->%s\n", data.cmd_lst->commands[0]);
	
        // printf("command[0]-->%s\n", data.cmd_lst->commands[0]);
		//  printf("command[1]-->%s\n", data.cmd_lst->commands[1]);
		//   printf("command[2]-->%s\n", data.cmd_lst->commands[2]);
        // printf("%s\n", data.cmd_lst->commands[0]);
        data.cmd_nb = commands_numbr(data);
        // printf("heereee\n");
        if(data.cmd_nb == 1 && builtin_only(data.cmd_lst->commands) && !signal_received)
            handle_builtins(&data, data.cmd_lst->commands);
        else if(!signal_received)
            excute_commands(&data);
        free_cmd(&data.cmd_lst);
		free_token(&data.token);
    }
    clear_env(&data.env_lst);
    free_all(&data, NULL, -1);
    return(0);
}
