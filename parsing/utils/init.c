#include "../../minishell.h"

void	init_data(t_data *data)
{
	data->token = NULL;
	data->env_lst = NULL;
	data->cmd_lst = NULL;
	data->exit_status = 0;
}