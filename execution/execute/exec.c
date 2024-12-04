#include "../../minishell.h"

void    execute_command(t_data *data, t_fd fd_, char **commands, int i)
{
    char *path;

	if (!is_builtin(commands[0]))
	{
		path = get_path(*data, commands[0]);
		check_path(path, commands[0]);
	}
	set_input_and_output(*data, fd_);
	set_read_write_pipe(*data, fd_, i);
	if (is_builtin(commands[0]))
	{
		handle_builtins(data, commands);
		exit(EXIT_SUCCESS);
	}
	else
	{
		execve(path, commands, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}
		
void	handle_child(t_data *data, t_cmd *tmp, t_fd fd_, int i)
{
	if(signal(SIGQUIT, SIG_DFL) == SIG_ERR)
	{
        perror("signal");
		exit(EXIT_FAILURE);
	}
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
	{
		perror("signal");
		exit(EXIT_FAILURE);
	}
	if (tmp->input_fd == -2 || tmp->output_fd == -2)
		exit(EXIT_FAILURE);
	execute_command(data, fd_, tmp->commands, i);

}

void	handle_childs(t_data *data, t_fd *fd_)
{
	int		i;
	t_cmd	*tmp;
	int		fd[2];
	int		pid[data->cmd_nb];

	i = 0;
	tmp = data->cmd_lst;
	while (tmp)
	{
		if(!create_pipe(data, fd, fd_, i))
			return;	
		pid[i] = fork();
		if (pid[i] == 0)
			handle_child(data, tmp, *fd_, i);
		else if (pid[i] > 0)
			save_read_of_pipe(*data, fd_, i);
		else
		{
			perror("fork");
			return ;
		}
		i++;
		tmp = tmp->next;
	}
	wait_pids(data, pid);
}

void	excute_commands(t_data *data)
{
	t_fd fd_;
	
	fd_.prev_fd = -1;
	if(signal(SIGQUIT, sigquit_child) == SIG_ERR)
	{
        perror("signal");
		return ;
	}
	if (signal(SIGINT, sigint_child) == SIG_ERR)
	{
		perror("signal");
		return ;
	}
	handle_childs(data, &fd_);
	if (signal(SIGINT, sigint_parent) == SIG_ERR)
	{
		perror("signal");
		return ;
	}
	if(signal(SIGQUIT, SIG_IGN) == SIG_ERR)
    {
		perror("signal");
		return ;
	}
}
