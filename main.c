/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 22:06:58 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/20 00:09:29 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_token(t_token *token)
// {
// 	t_token	*tmp;

// 	tmp = token;
// 	while (tmp->next != token)
// 	{
// 		printf("Type : %d, [%s]\n", tmp->type, tmp->str);
// 		tmp = tmp->next;
// 	}
// 	printf("Type : %d, [%s]\n",  tmp->type, tmp->str);
// }

// void	print_tab(char **tab)
// {
// 	int	i;

// 	if (!(tab))
// 	{
// 		printf("NULL");
// 		return ;
// 	}
// 	i = 0;
// 	printf("[");
// 	while (tab[i])
// 	{
// 		printf("%s", tab[i]);
// 		if (tab[i + 1])
// 			printf(", ");
// 		i++;
// 	}
// 	printf("]");
// }

// void	print_cmd(t_cmd *cmd)
// {
// 	t_cmd	*tmp;

// 	tmp = cmd;
// 	while (tmp->next != cmd)
// 	{
// 		printf("Skip -> %d, infile -> %d, outfile -> %d, cmd : ",
// 		tmp->skip_cmd, tmp->input_fd, tmp->output_fd);
// 		print_tab(tmp->commands);
// 		printf("\n");
// 		tmp = tmp->next;
// 	}
// 	printf("Skip -> %d, infile -> %d, outfile -> %d, cmd : ", tmp->skip_cmd,
// 		 tmp->input_fd, tmp->output_fd);
// 	print_tab(tmp->commands);
// 	printf("\n");
// }

void	handle_line(t_data *data, char *line)
{
	add_history(line);
	// printf("--->%p\n", &line);
	free(line);
	data->cmd_nb = commands_numbr(*data);
	if (data->cmd_nb == 1 && builtin_only(data->cmd_lst->commands)
		&& !g_signal_received)
	{
		if (data->cmd_lst->input_fd == -1 || data->cmd_lst->output_fd == -1)
		{
			data->exit_status = 1;
			return ;
		}
		handle_builtins(data, data->cmd_lst->commands);
	}
	else if (!g_signal_received)
		excute_commands(data);
	free_cmd(&data->cmd_lst);
	free_token(&data->token);
	// system("leaks minishell");
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
		g_signal_received = 0;
		line = readline(prompt);
		if (!line)
			handle_end_of_file();
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
