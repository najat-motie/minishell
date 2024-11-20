#include "minishell.h"

char *get_path(t_data data, char *command)
{
    int i = 0;
    int j = 0;
    // char *path = getenv("PATH");
    char *path = retreive_value(data, "PATH");
    if(path == NULL)
        return(NULL);
    char **all_paths = ft_split(path, ':');
    char *full_path;
    while(all_paths != NULL && all_paths[i] != NULL)
    {
        full_path = malloc((ft_strlen(all_paths[i]) + ft_strlen(command) + 2) * sizeof(char));
        j = 0;
        while (all_paths[i][j] != '\0')
        {
            full_path[j] = all_paths[i][j];
            j++;
        }
        int k = 0;
        char *get_cmnd = ft_strrchr(command, '/');
        if(get_cmnd != NULL)
        {
            while (get_cmnd[k] != '\0')
            {
                full_path[j] = get_cmnd[k];
                j++;
                k++;
            }
            full_path[j] = '\0';
            if(access(full_path, X_OK) == 0 && ft_strncmp(full_path, command, ft_strlen(command)) == 0)
                return(full_path);
        }
        else
        {
            full_path[j] = '/';
            j++;
            while (command[k] != '\0')
            {
                full_path[j] = command[k];
                j++;
                k++;
            }
            full_path[j] = '\0';
            if(access(full_path, X_OK) == 0)
                return(full_path);
        }
        free(full_path);
        i++;
    }
    return(NULL);
}

void    excute_cmnds(t_data *data)
{
    int i = 0;
    int status;
    pid_t pid;
    int fd[2];
    int prev_fd = -1;
    int *pids = malloc(data->cmd_nb * sizeof(int));
    t_cmd *tmp = data->cmd_lst;
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
        if(signal(SIGINT, handle_sigint_child_process) == SIG_ERR)
                perror("signal");
        // printf("%d | %d | %d\n", fd[0], fd[1], prev_fd);
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
            if(i > 0 && tmp->fd_input == -1)
            {
                if(dup2(prev_fd, 0) == -1)
                {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
                close(prev_fd);
                // char buffer[10];
                // read(0, buffer, 8);
                // buffer[8] = 0;
                // printf("%s\n", buffer);
            }
            if(i < data->cmd_nb - 1 && tmp->fd_output == -1)
            {      
                close(fd[0]);
                if(dup2(fd[1], 1) == -1)
                {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
                close(fd[1]);
            }
            if(tmp->fd_input != -1)
            {
               close(fd[0]); 
                if(dup2(tmp->fd_input, 0) == -1)
                {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
                close(tmp->fd_input);
            }
            if(tmp->fd_output != -1)
            {
                close(fd[1]);
                if(dup2(tmp->fd_output, 1) < 0)
                {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
                close(tmp->fd_output);
            }
            if(is_builtin(tmp->commands[0]))
            {
                // fprintf(stderr, "5--> i %d | cmd %d\n", i, data->cmd_nb);
                builtin_commands(data, tmp->commands);
                exit(EXIT_SUCCESS);
            }
            else
            {
                char **argv = tmp->commands;
                char *envp[] = {NULL};
                char *path = get_path(*data, tmp->commands[0]);
                if(!path)
                {
                    printf("%s: command not found\n", tmp->commands[0]);
                    exit(EXIT_FAILURE);
                }
                execve(path, argv, envp);
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }
        else if(pid > 0)
        {
            close(prev_fd);
            if(i < data->cmd_nb - 1)
            {
                close(fd[1]);
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
        waitpid(pids[i], &status, 0);
        i++;
    }
    if(signal(SIGINT, handle_sigint) == SIG_ERR)
                perror("signal");
}
