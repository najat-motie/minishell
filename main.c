#include "minishell.h"

void	init_data(t_data *data)
{
	data->token = NULL;
	data->env_lst = NULL;
	data->cmd_lst = NULL;
	data->exit_status = 0;
}

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
//     t_data	data;

// 	atexit(leaks);
// 	init_data(&data, argc, argv);

   
//     if(data->line == NULL)
//         exit(EXIT_SUCCESS);
//     if(*data->line != '\0')
//         add_history(data->line);
//     data->cmd_nb = commands_numbr(*data);
//     if(data->cmd_lst)
//     {
//         handle_redirects(data);
//         if(data->cmd_nb == 1 && builtin_only(data->cmd_lst->commands) && !signal_received)
//             handle_builtins(data, data->cmd_lst->commands);
//         else if(!signal_received)
//             excute_commands(data);
//     }
//     clear_resources(data);
//     system("leaks minishell");
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
			continue;
        data.cmd_nb = commands_numbr(data);
        handle_redirects(&data);
        if(data.cmd_nb == 1 && builtin_only(data.cmd_lst->commands) && !signal_received)
            handle_builtins(&data, data.cmd_lst->commands);
        else if(!signal_received)
            excute_commands(&data);
        free_cmd(&data.cmd_lst);
		free_token(&data.token);
    }
    clear_env(&data.env_lst);
    return(0);
}
