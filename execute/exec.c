#include "../minishell.h"

char *check_current_working_directory(char *command)
{
    char *path;
    char *pwd = get_pwd();
    if(!pwd)
    {
        perror("getcwd");
        return(NULL);
    }
    path = ft_strjoin(ft_strjoin(pwd, "/"), command);
    if(access(path, X_OK) == 0)
        return(path);
    else
    {
        perror(command);
        return(NULL);
    }
}

char *get_path(t_data data, char *command)
{
    int i = 0;
    char *path;
    if(!command)
        return(NULL);
    if(ft_strchr(command, '/') != NULL || ft_strchr(command, '.') != NULL)
    {
        if(access(command, X_OK) == 0)
            return(command);
        else
        {
            perror(command);
            return(NULL);
        }
    }
    path = retreive_value(data, "PATH");
    if(path == NULL)
    {
        path = check_current_working_directory(command);
        if(path)
            return(path);
        return(NULL);
    }
    char **all_paths = ft_split(path, ':');
    char *full_path;
    while(all_paths != NULL && all_paths[i] != NULL)
    {
        full_path = ft_strjoin(ft_strjoin(all_paths[i], "/"), command);
        if(access(full_path, X_OK) == 0)
            return(full_path);
        i++;
    }
    return("not valid command");
}

void    excute_cmnds(t_data *data)
{
    int i = 0;
    int status;
    char **argv;
    char *path;
    pid_t pid;
    int fd[2];
    int prev_fd = -1;
    int *pids = malloc(data->cmd_nb * sizeof(int));
    if(pids == NULL)
    {
        perror("malloc");
        return ;
    }
    t_cmd *tmp = data->cmd_lst;
    if(signal(SIGINT, sigint_child) == SIG_ERR)
            perror("signal");
    while(tmp)
    {
        if(i < data->cmd_nb - 1)
        {
            if(pipe(fd) == -1)
            {
                perror("pipe");
                data->exit_status = 1;
                return ;
            }
        }
        pid = fork();
        pids[i] = pid;
        if(pid == 0)
        {
            if(signal(SIGINT, SIG_DFL) == SIG_ERR)
            {
                perror("signal");
                exit(EXIT_FAILURE);
            }
            if(tmp->fd_input == -2 || tmp->fd_output == -2)
                exit(EXIT_FAILURE);
            if(!is_builtin(tmp->commands[0]))
            {
                argv = tmp->commands;
                path = get_path(*data, tmp->commands[0]);
                if(ft_strcmp(path, "not valid command") == 0)
                {
                    printf("%s: command not found\n", tmp->commands[0]);
                    exit(127);
                }
                else if(!path  && tmp->commands[0])
                    exit(EXIT_FAILURE);
                else if(!path  && !tmp->commands[0])
                    exit(EXIT_SUCCESS);
            }
            if(i > 0 && tmp->fd_input == -1)
            {
                if(dup2(prev_fd, 0) == -1)
                {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
                if(close(prev_fd) == -1)
                    perror("close");
            }
            if(i < data->cmd_nb - 1 && tmp->fd_output == -1)
            {      
                if(close(fd[0]) == -1)
                    perror("close");
                if(dup2(fd[1], 1) == -1)
                {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
                if(close(fd[1]) == -1)
                    perror("close");
            }
            if(tmp->fd_input != -1)
            {
                if(close(fd[0]) == -1)
                    perror("close"); 
                if(dup2(tmp->fd_input, 0) == -1)
                {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
                if(close(tmp->fd_input) == -1)
                    perror("close");
            }
            if(tmp->fd_output != -1)
            {
                if(close(fd[1]) == -1)
                    perror("close");
                if(dup2(tmp->fd_output, 1) < 0)
                {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
                if(close(tmp->fd_output) == -1)
                    perror("close");
            }
            if(is_builtin(tmp->commands[0]))
            {
                handle_builtins(data, tmp->commands);
                exit(EXIT_SUCCESS);
            }
            else
            {
                execve(path, argv, NULL);
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }
        else if(pid > 0)
        {
            if(prev_fd != -1)
            {
                if(close(prev_fd) == -1)
                    perror("close");
            }
            if(i < data->cmd_nb - 1)
            {
                if(close(fd[1]) == -1)
                    perror("close");
                prev_fd = fd[0];
            }
        }
        else
        {
            perror("fork");
            return ;
        }
        i++;
        data->exit_status = 0;
        tmp = tmp->next;
    }
    i = 0;
    while(i < data->cmd_nb)
    {
        if(waitpid(pids[i], &status, 0) == -1)
        {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        if(WIFEXITED(status))
            data->exit_status = WEXITSTATUS(status);
        else if(WIFSIGNALED(status))
            data->exit_status = WTERMSIG(status) + 128;
        i++;
    }
    if(signal(SIGINT, sigint_parent) == SIG_ERR)
                perror("signal");
}
