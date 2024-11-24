#include "../../minishell.h"

void    read_input(t_data data, int fd, char *delimeter)
{
    char *input;

    while(1)
    {
        input = readline("> ");
        if(!input)
            break;
        if(data.cmd_lst->red_lst->not_quouted)
            input = expand_input(data, input);
        if(ft_strcmp(input, delimeter) == 0)
        {
            free(input);
            break;
        }
        write(fd, input, ft_strlen(input));
        write(fd, "\n", 1);
        free(input);
    }
}

int    handle_heredoc(t_data *data, char *delimeter)
{
    int in;
    int fd[2];

    in = dup(0);
    if(pipe(fd) == -1)
        perror("pipe");
    if(signal(SIGINT, sigint_heredoc) == SIG_ERR)
        perror("signal");
    read_input(*data, fd[1], delimeter);
    if(signal_received)
    {
        data->exit_status = 1;
        dup2(in, 0);
        close(in);
    }
    else
    {
        data->exit_status = 0;
        close(in);
    }
    if(signal(SIGINT, sigint_parent_without_newline) == SIG_ERR)
        perror("signal");
    close(fd[1]);
    return(fd[0]);
}

