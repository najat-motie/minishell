#include "../minishell.h"

void    sigint_parent(int signum)
{
    (void)signum;
    received_signal = 1;
    write(1, "\n", 1);
    write(1, "minishell> ", 11);
}

void    sigint_heredoc(int signum)
{
    (void)signum;
    received_signal = 1;
    write(STDOUT_FILENO, "\n", 1);
    close(0);
}

void    sigint_child(int signum)
{
    (void)signum;
    write(1, "\n", 1);
}

void    handle_eof(t_data data)
{
    if(data.input == NULL)
    {
        write(1, "exit\n", 5);    
        exit(EXIT_SUCCESS);
    }
}