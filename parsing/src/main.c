

#include "../include/minishell.h"

int	make_env(t_data *data, char **env)
{
	t_list	*list;
	int		i;
	char	*tmp;

	if (!(*env))
		return (make_env2(data));
	i = -1;
	list = NULL;
	while (env[++i])
	{
		tmp = ft_strdup(env[i]);
		if (!tmp)
			return (free_list(&list));
		if (!append(&list, tmp))
			return (free_list(&list));
	}
	data->env = list;
	return (1);
}

void	init_data(t_data *data, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	data->env = NULL;
	data->token = NULL;
	data->cmd = NULL;
	data->exit_code = 0;
	data->pip[0] = -1;
	data->pip[1] = -1;
}


bool	parseline(t_data *data, char *line)
{
	if (open_quote(data, line))
	{
		free(line);
		return (false);
	}
	if (!replace_dollar(&line, data) || !create_list_token(&data->token, line))
	{
		free(line);
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	}
	free(line);
	print_token(data->token);
	if (data->token && data->token->prev->type == PIPE)
	{
		write(2, "Error: Unclosed pipe\n", 21);
		data->exit_code = 2;
		free_token(&data->token);
		return (false);
	}
	if (!data->token || !create_list_cmd(data))
	{
		free_token(&data->token);
		free_cmd(&data->cmd);
		return (false);
	}
	print_cmd(data->cmd);
	return (check_pipe(data));
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*line;

	init_data(&data, argc, argv);
	if (!make_env(&data, env))
		free_all(&data, ERR_MALLOC, EXT_MALLOC);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			free_all(&data, "exit\n", data.exit_code);
		if (!parseline(&data, line))
			return 0 ;
		free_cmd(&data.cmd);
		free_token(&data.token);
	}
	free_all(&data, NULL, -1);
	return (0);
}
