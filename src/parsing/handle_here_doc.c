
#include "../../include/minishell.h"


int before_start()
{
    int in = dup(0);
    if(in == -1)
    {
        perror("dup");
        return(-1);
    }
    // if(signal(SIGINT, sigint_heredoc) == SIG_ERR)
    // {
    //     perror("signal");
    //     return(-1);
    // }
    return(in);
}

void    write_to_file(int fd, char *input)
{
    write(fd, input, ft_strlen(input));
    write(fd, "\n", 1);
}

void    read_input(t_data *data, int fd, char *delimeter,int quote)
{
    char *input;

	// int fd_1 = open("heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    while(1)
    {
        input = readline("> ");
		// buf = NULL;
// 		buf = readline("> ");
		if (!input)
		{
			print_error("warning: here-document delimited by end-of-file ");
			print_error("(wanted '");
			print_error(delimeter);
			print_error("')\n");
			break ;
		}
        printf("delemiter: %s\n", delimeter);
		if (!ft_strncmp(delimeter,input, INT_MAX))
			break ;
        if(!quote)
        {
            if(!replace_dollar(&input, data))
			free_all(data, ERR_MALLOC, EXT_MALLOC);
        }

        // if(!input)
        //     break;
        // if(data.cmd_lst->red_lst->not_quouted)
        //     input = expand_input(data, input);
        // if(ft_strcmp(input, delimeter) == 0)
        // {
        //     free(input);
        //     break;
        // }
        write_to_file(fd, input);
		// write(fd_1, input, ft_strlen(input));
        free(input);
    }
}

int    set_exit_status(t_data *data, int in)
{
    if(signal_received)
    {
        data->exit_code = 1;
        if(dup2(in, 0) == -1)
        {
            perror("dup2");
            return(-1);
        }
        close(in);
    }
    else
    {
        data->exit_code = 0;
        close(in);
    }
    return(1);
}

int    handle_heredoc(t_data *data, char *delimeter,int *quote)
{
    int in;
    int fd[2];
	// char buff[100];

	// int fd_1 = open("heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    in = before_start();
    if(in == -1)
        return(-1);
    if(pipe(fd) == -1)
    {
        perror("pipe");
        return(-1);
    }
    read_input(data, fd[1], delimeter,*quote);
	// read(fd[1], buff, 100);
	// write(1, buff, 100);
    if(set_exit_status(data, in) == -1)
        return(-1);
    // if(signal(SIGINT, sigint_parent_without_newline) == SIG_ERR)
    // {
    //     perror("signal");
    //     return(-1);
    // }
    close(fd[1]);
    return(fd[0]);
}