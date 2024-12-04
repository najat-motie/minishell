#include "../../minishell.h"

int before_start()
{
    int in = dup(0);
    if(in == -1)
    {
        perror("dup");
        return(-1);
    }
    if(signal(SIGINT, sigint_heredoc) == SIG_ERR)
    {
        perror("signal");
        return(-1);
    }
    return(in);
}

void    write_to_file(int fd, char *input)
{
    write(fd, input, ft_strlen(input));
    write(fd, "\n", 1);
}

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
        write_to_file(fd, input);
        free(input);
    }
}

int    set_exit_status(t_data *data, int in)
{
    if(signal_received)
    {
        data->exit_status = 1;
        if(dup2(in, 0) == -1)
        {
            perror("dup2");
            return(-1);
        }
        close(in);
    }
    else
    {
        data->exit_status = 0;
        close(in);
    }
    return(1);
}

int    handle_heredoc(t_data *data, char *delimeter)
{
    int in;
    int fd[2];

    in = before_start();
    if(in == -1)
        return(-1);
    if(pipe(fd) == -1)
    {
        perror("pipe");
        return(-1);
    }
    read_input(*data, fd[1], delimeter);
    if(set_exit_status(data, in) == -1)
        return(-1);
    if(signal(SIGINT, sigint_parent_without_newline) == SIG_ERR)
    {
        perror("signal");
        return(-1);
    }
    close(fd[1]);
    return(fd[0]);
}
