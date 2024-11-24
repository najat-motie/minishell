#include "../minishell.h"

int    redirect_output(char *file_name)
{
    int fd;

    fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
    if(fd == -1)
    {
        perror("open");
        fd = -2;
    }
    return(fd);
}

int    redirect_input(char *file_name)
{
    int fd;

    fd = open(file_name,  O_RDONLY);
    if(fd == -1)
    {
        perror("open");
        fd = -2;
    }
    return(fd);
}

int    redirect_append(char *file_name)
{
    int fd;

    fd = open(file_name,  O_RDWR | O_CREAT | O_APPEND, 0777);
    if(fd == -1)
    {
        perror("open");
        fd = -2;
    }
    return(fd);
}

char *retreive_value(t_data data, char *key)
{
    t_env *env_tmp = data.env_lst;

    while(env_tmp)
    {
        if(ft_strcmp(env_tmp->key, key) == 0)
            return(env_tmp->value);           
        env_tmp = env_tmp->next;
    }
    return(NULL);
}

int dollar_count(char *heredoc_input)
{
    int i = 0;
    int count = 0;
    while(heredoc_input[i])
    {
        if(heredoc_input[i] == '$' && ((heredoc_input[i + 1] >= 'a' && heredoc_input[i + 1] <= 'z') || (heredoc_input[i + 1] >= 'A' && heredoc_input[i + 1] <= 'Z') || (heredoc_input[i + 1] == '_')))
            count++;
        i++;
    }
    return(count);
}

char    *expand_input(t_data data, char *heredoc_input)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    int n = 0;
    char *to_expand = NULL;
    int removed_count = 0;
    int dollar = dollar_count(heredoc_input);
    char **expanded = malloc((dollar + 1) * sizeof(char *));
    if(expanded == NULL)
    {
        perror("malloc");
        return(NULL);
    }
    while(heredoc_input[i])
    {
        if(heredoc_input[i] == '$')
        {
            if((heredoc_input[i + 1] >= 'a' && heredoc_input[i + 1] <= 'z') || (heredoc_input[i + 1] >= 'A' && heredoc_input[i + 1] <= 'Z') || (heredoc_input[i + 1] == '_'))
            {
                i++;
                removed_count++;
                k = 0;
                l = i;
                while((heredoc_input[l] >= 'a' && heredoc_input[l] <= 'z') || (heredoc_input[l] >= 'A' && heredoc_input[l] <= 'Z') || (heredoc_input[l] >= '0' && heredoc_input[l] <= '9') || (heredoc_input[l] == '_'))
                {
                    l++;
                    k++;
                }
                to_expand = malloc(k + 1);
                if(to_expand == NULL)
                {
                    perror("malloc");
                    return(NULL);
                }
                k = 0;
                while((heredoc_input[i] >= 'a' && heredoc_input[i] <= 'z') || (heredoc_input[i] >= 'A' && heredoc_input[i] <= 'Z') || (heredoc_input[i] >= '0' && heredoc_input[i] <= '9') || (heredoc_input[i] == '_'))
                    to_expand[k++] = heredoc_input[i++];
                i--;
                to_expand[k] = '\0';
                expanded[n++] = retreive_value(data, to_expand);
            }
        }
        i++;
    }
    expanded[n] = NULL;
    n = 0;
    int count = 0;
    while(expanded[n])
    {
        count += ft_strlen(expanded[n]);
        n++;
    }
    char *input = malloc(ft_strlen(heredoc_input) - ft_strlen(to_expand) - removed_count + count + 1);
    if(!input)
    {
        perror("malloc");
        return(NULL);
    }
    i = 0;
    j = 0;
    k = 0;
    l = 0;
    n = 0;
    while(heredoc_input[i])
    {
        while(heredoc_input[i] && heredoc_input[i] != '$')
            input[j++] = heredoc_input[i++];
        if(heredoc_input[i] == '$')
        {
            l = i;
            if((heredoc_input[l + 1] >= 'a' && heredoc_input[l + 1] <= 'z') || (heredoc_input[l + 1] >= 'A' && heredoc_input[l + 1] <= 'Z') || (heredoc_input[l + 1] == '_'))
            {
                l++;
                k = 0;
                while(expanded[n] && expanded[n][k])
                    input[j++] = expanded[n][k++];
                while((heredoc_input[l] >= 'a' && heredoc_input[l] <= 'z') || (heredoc_input[l] >= 'A' && heredoc_input[l] <= 'Z') || (heredoc_input[l] >= '0' && heredoc_input[l] <= '9') || (heredoc_input[l] == '_'))
                    l++;
                i = l;
                n++;
            }
            else
                input[j++] = heredoc_input[i];   
        }
    }
    input[j] = '\0';
    return(input);
}

int    handle_heredoc(t_data *data, char *delimeter)
{
    int in;
    int fd[2];
    char *input;

    if(pipe(fd) == -1)
        perror("pipe");
    in = dup(0);
    if(in == -1)
        perror("dup");
    if(signal(SIGINT, sigint_heredoc) == SIG_ERR)
        perror("signal");
    while(1)
    {
        input = readline("> ");
        if(!input)
            break;
        if(data->cmd_lst->red_lst->not_quouted)
            input = expand_input(*data, input);
        if(ft_strcmp(input, delimeter) == 0)
        {
            free(input);
            break;
        }
       if( write(fd[1], input, ft_strlen(input)) == -1)
            perror("write");
        if(write(fd[1], "\n", 1))
            perror("write");
        free(input);
    }
    if(signal_received)
    {
        data->exit_status = 1;
        if(dup2(in, 0) == -1)
            perror("dup2");
        if(close(in) == -1)
            perror("close");
    }
    else
    {
        data->exit_status = 0;
        if(close(in) == -1)
            perror("close");
    }
    if(signal(SIGINT, sigint_parent_without_newline) == SIG_ERR)
        perror("signal");
    if(close(fd[1]) == -1)
        perror("close");
    return(fd[0]);
}

void    handle_redirects(t_data *data)
{
    t_cmd *tmp_cmd = NULL;
    t_red *tmp_red = NULL;
    tmp_cmd = data->cmd_lst;
    while(tmp_cmd && !signal_received)
    {
        tmp_red = tmp_cmd->red_lst;
        while(tmp_red && !signal_received)
        {
            if(ft_strcmp(tmp_red->symbol_type, "<<") == 0)
            {
                if(close(tmp_cmd->fd_heredoc) == -1)
                    perror("close");
                tmp_cmd->fd_heredoc = handle_heredoc(data, tmp_red->file_name);
            }
            tmp_red = tmp_red->next;
        }
        tmp_cmd = tmp_cmd->next;
    }
    if(data->cmd_lst)
        tmp_cmd = data->cmd_lst;
    while(tmp_cmd && !signal_received)
    {
        tmp_red = tmp_cmd->red_lst;
        while(tmp_red && !signal_received)
        {
            if(tmp_cmd->fd_input == -2 || tmp_cmd->fd_output == -2)
                break ;
            if(ft_strcmp(tmp_red->symbol_type, ">") == 0)
            {
                if(close(tmp_cmd->fd_output) == -1)
                    perror("close");
                tmp_cmd->fd_output = redirect_output(tmp_red->file_name);
            }
            if(ft_strcmp(tmp_red->symbol_type, ">>") == 0)
            {
                if(close(tmp_cmd->fd_output) == -1)
                    perror("close");
                tmp_cmd->fd_output = redirect_append(tmp_red->file_name);
            }
            if(ft_strcmp(tmp_red->symbol_type, "<") == 0)
            {
                if(close(tmp_cmd->fd_input) == -1)
                    perror("close");
                tmp_cmd->fd_input = redirect_input(tmp_red->file_name);
            }
            if(ft_strcmp(tmp_red->symbol_type, "<<") == 0)
            {
                if(close(tmp_cmd->fd_input) == -1)
                    perror("close");
                tmp_cmd->fd_input = tmp_cmd->fd_heredoc;
            }
            tmp_red = tmp_red->next;
        }
        tmp_cmd = tmp_cmd->next;
    }
}
