/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ner-roui <ner-roui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:22:22 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/20 13:56:17 by ner-roui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_sigint(int signum)
{
	(void)signum;
	g_signal_received = 1;
	// rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_parent_change_behavior_in_heredoc(int signum)
{
	(void)signum;
	g_signal_received = 1;
	write(STDOUT_FILENO, "\n", 1);
	close(0);
}

// the readline function after receive end of file (ctrl+d or close stdin)
// prints newline by default, so here no need to add newline for sigint handle
void	handle_sigint_without_newline(int signum)
{
	(void)signum;
	g_signal_received = 1;
	// rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_parent_change_behavior_in_child(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
}

void	handle_sigquit_in_child(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "Quit: 3\n", 8);
}
