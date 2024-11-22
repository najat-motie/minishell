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

int main(int argc, char **argv, char **envp) 
{
    (void)argc;
    (void)argv;
    t_data data;
    data.exit_status = 0;
    if(signal(SIGQUIT, SIG_IGN) == SIG_ERR)
        perror("signal");
    if(signal(SIGINT, sigint_parent) == SIG_ERR)
        perror("signal");
    data.envp = envp;
    fill_env_lst(&data);
    char *prompt = "minishell> ";
    while (1)
    {
        write(1, prompt, ft_strlen(prompt));
        data.input = get_next_line(0);
        handle_eof(data);
        if(*data.input != '\0')
            add_history(data.input);
        received_signal = 0;
        fill_cmd_lst(&data);
        data.cmd_nb = commands_numbr(data);
        if(data.cmd_lst)
        {
            handle_redirects(&data);
            if(data.cmd_nb == 1 && builtin_only(data.cmd_lst->commands) && received_signal == 0)
                handle_builtins(&data, data.cmd_lst->commands);
            else if(!received_signal)
                excute_cmnds(&data);
        }
    }
    return 0;
}
