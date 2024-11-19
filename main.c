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

void other_commands(t_data data, char **commands) 
{

    if (commands[0] != NULL)
    {
        pid_t pid = fork();
        int status;
        if (pid == 0) 
        {
            char **argv = commands;   
            char *path = get_path(data, commands[0]);
            if(!path)
            {
                printf("%s: command not found\n", commands[0]);
                    exit(EXIT_FAILURE);
            }
            char *envp[] = {NULL};
            execve(path, argv, envp);
            free(path);
            perror("execve");
            exit(EXIT_FAILURE);
        }
        else if (pid > 0)
            waitpid(pid, &status, 0);
        else
            perror("fork");
    }
}

int main(int argc, char **argv, char **envp) 
{
    (void)argc;
    (void)argv;
    t_data data;
    data.exit_status = 0;
    int in;
    int out;
    if(signal(SIGQUIT, SIG_IGN) == SIG_ERR)
        perror("signal");
    data.envp = envp;
    fill_env_lst(&data);
    fill_export_lst(&data);
    char *prompt = "minishell> ";
    while (1)
    {
        data.input = readline(prompt);
        if(!data.input)
            break;
        add_history(data.input);
        received_signal = 0;
        fill_cmd_lst(&data);
        data.cmd_nb = commands_numbr(data);
        if(data.cmd_lst)
        {
            handle_redirects(&data);
            if(data.cmd_nb > 1 && !received_signal)
                excute_cmnds(&data);
            else if(!received_signal)
            {
                if(data.cmd_lst->fd_input == -2 || data.cmd_lst->fd_output == -2)
                    continue;
                if(data.cmd_lst->fd_input != -1)
                {
                    in = dup(0);
                    if(in < 0)
                        perror("dup");
                    if(dup2(data.cmd_lst->fd_input, 0) < 0)
                        perror("dup2");
                    close(data.cmd_lst->fd_input);
                }
                if(data.cmd_lst->fd_output != -1)
                {
                    out = dup(1);
                    if(out < 0)
                        perror("dup");
                    if(dup2(data.cmd_lst->fd_output, 1) < 0)
                        perror("dup2");
                    close(data.cmd_lst->fd_output);
                }
                if(is_builtin(data.cmd_lst->commands[0]))
                    builtin_commands(&data, data.cmd_lst->commands);
                else
                    other_commands(data, data.cmd_lst->commands);
                if(data.cmd_lst->fd_output != -1)
                {
                    if(dup2(out, 1) < 0)
                        perror("dup2");
                    close(out);
                }
                if(data.cmd_lst->fd_input != -1)
                {
                    if(dup2(in, 0) < 0)
                        perror("dup2");
                    close(in);
                }
            }
        }
    }
    return 0;
}
