#include "minishell.h"

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

void    clear_resources(t_data *data)
{
    free(data->input);
    lstclear_cmd(&data->cmd_lst);
}

int commands_numbr(t_data data)
{
    int nb = 0;
    t_cmd *tmp = data.cmd_lst;
    while(tmp)
    {
        nb++;
        tmp = tmp->next;
    }
    return(nb);
}

void    handle_input(t_data *data, char *prompt)
{
    data->input = readline(prompt);
    if(data->input == NULL)
        exit(EXIT_SUCCESS);
    if(*data->input != '\0')
        add_history(data->input);
    signal_received = 0;
    fill_cmd_lst(data);
    data->cmd_nb = commands_numbr(*data);
    if(data->cmd_lst)
    {
        handle_redirects(data);
        if(data->cmd_nb == 1 && builtin_only(data->cmd_lst->commands) && !signal_received)
            handle_builtins(data, data->cmd_lst->commands);
        else if(!signal_received)
            excute_commands(data);
    }
    clear_resources(data);
    // system("leaks minishell");
}

int main(int argc, char **argv, char **envp) 
{
    (void)argc;
    (void)argv;
    t_data data;
    char *prompt = "minishell> ";

    if(signal(SIGQUIT, SIG_IGN) == SIG_ERR)
        perror("signal");
    if(signal(SIGINT, sigint_parent) == SIG_ERR)
        perror("signal");
    data.exit_status = 0;
    data.envp = envp;
    fill_lst(&data);
    while (1)
        handle_input(&data, prompt);
    lstclear_env(&data.env_lst);
    return(0);
}
