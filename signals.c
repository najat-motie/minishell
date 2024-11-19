#include "minishell.h"
void    handle_sigint(int signum)
{
    (void)signum;
    received_signal = 1;
    rl_replace_line("", 0);
    rl_on_new_line();
    write(STDOUT_FILENO, "\n", 1);
    rl_redisplay();   
}

void    handle_sigint_in_heredoc(int signum)
{
    (void)signum;
    printf("\n");
}
