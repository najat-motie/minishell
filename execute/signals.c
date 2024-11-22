#include "../minishell.h"

void    sigint_parent(int signum)
{
    (void)signum;
    received_signal = 1;
    rl_replace_line("", 0);
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_redisplay();   
}

void    sigint_parent_without_newline(int signum)
{
    (void)signum;
    received_signal = 1;
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();   
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
    write(STDOUT_FILENO, "\n", 1);
}

void    handle_eof(t_data data)
{
    if(data.input == NULL)
        exit(EXIT_SUCCESS);
}