/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:23:29 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/14 16:23:30 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data)
{
	data->token = NULL;
	data->env_lst = NULL;
	data->cmd_lst = NULL;
	data->exit_status = 0;
}

void	catch_signals(void)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("signal");
	if (signal(SIGINT, sigint_parent) == SIG_ERR)
		perror("signal");
}

int	commands_numbr(t_data data)
{
	int		nb;
	t_cmd	*tmp;

	nb = 0;
	tmp = data.cmd_lst;
	if (tmp)
	{
		nb++;
		tmp = tmp->next;
	}
	while (tmp != data.cmd_lst)
	{
		nb++;
		tmp = tmp->next;
	}
	return (nb);
}

void	handle_line(t_data *data, char *line)
{
	if (*line != '\0')
		add_history(line);
	data->cmd_nb = commands_numbr(*data);
	handle_redirects(&data);
	if (data->cmd_nb == 1 && builtin_only(data->cmd_lst->commands)
		&& !signal_received)
		handle_builtins(&data, data->cmd_lst->commands);
	else if (!signal_received)
		excute_commands(&data);
	free_cmd(&data->cmd_lst);
	free_token(&data->token);
	free(line);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;
	char	*prompt;

	(void)argc;
	(void)argv;
	prompt = "minishell> ";
	catch_signals();
	init_data(&data);
	make_env(&data, envp);
	while (1)
	{
		signal_received = 0;
		line = readline(prompt);
		if (!line)
			exit(EXIT_SUCCESS);
		if (empty_line(line))
			continue ;
		if (!parseline(&data, line))
			continue ;
		handle_line(&data, line);
	}
	free(line);
	clear_env(&data.env_lst);
	return (0);
}
