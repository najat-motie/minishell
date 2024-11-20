#include "../minishell.h"
void    handle_sigint(int signum)
{
    (void)signum;
    received_signal = 1;
    rl_replace_line("", 0);
    rl_on_new_line();
    write(STDOUT_FILENO, "\n", 1);
    rl_redisplay();   
}

void    handle_eof(t_data data)
{
    if(data.input == NULL)
        exit(EXIT_SUCCESS);
}

void    handle_sigint_in_child_process(int signum)
{
    (void)signum;
    printf("\n");
}

void disable_echo_ctrl()
{
    struct termios term;

    if (tcgetattr(STDIN_FILENO, &term) == -1)
    {
        perror("tcgetattr");
        return;
    }
    term.c_lflag &= ~ECHOCTL;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
        perror("tcsetattr");
}
