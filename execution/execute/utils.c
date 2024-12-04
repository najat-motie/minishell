#include "../../minishell.h"

void	set_input_and_output(t_data data, t_fd fd)
{
	if (data.cmd_lst->input_fd != -1)
	{
		close(fd.read_pipe);
		if (dup2(data.cmd_lst->input_fd, 0) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(data.cmd_lst->input_fd);
	}
	if (data.cmd_lst->output_fd != -1)
	{
		close(fd.write_pipe);
		if (dup2(data.cmd_lst->output_fd, 1) < 0)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(data.cmd_lst->output_fd);
	}
}

void	set_read_write_pipe(t_data data, t_fd fd, int i)
{
	if (i > 0 && data.cmd_lst->input_fd == -1)
	{
		if (dup2(fd.prev_fd, 0) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(fd.prev_fd);
	}
	if (i < data.cmd_nb - 1 && data.cmd_lst->output_fd == -1)
	{
		close(fd.read_pipe);
		if (dup2(fd.write_pipe, 1) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(fd.write_pipe);
	}
}

void	save_read_of_pipe(t_data data, t_fd *fd, int i)
{
	if (fd->prev_fd != -1)
		close(fd->prev_fd);
	if (i < data.cmd_nb - 1)
	{
		close(fd->write_pipe);
		fd->prev_fd = fd->read_pipe;
	}
}

int	create_pipe(t_data *data, int fd[], t_fd *fd_, int i)
{
	if(i < data->cmd_nb - 1)
    {
        if(pipe(fd) == -1)
        {
            perror("pipe");
            data->exit_status = 1;
            return 0;
        }
    }
	fd_->read_pipe = fd[0];
	fd_->write_pipe = fd[1];
	return(1);
}

void	wait_pids(t_data *data, int *pids)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->cmd_nb)
	{
		if (waitpid(pids[i], &status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->exit_status = WTERMSIG(status) + 128;
		i++;
	}
}
