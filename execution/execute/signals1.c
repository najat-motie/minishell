/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:22:22 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/24 11:29:04 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// ->rl_redisplay(): Redraws the prompt for the user.
// ->rl_on_new_line(): notify readline that the cursor has moved to a new line 
// 	 and Prepares it to redraw the prompt on the new line.
void	handle_sigint_parent(int signum)
{
	(void)signum; 
	g_signal_received = 1;
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

// close the input of readline in herdoc to handle sigint signal
void	handle_sigint_parent_in_heredoc(int signum)
{
	(void)signum;
	g_signal_received = 1;
	write(STDOUT_FILENO, "\n", 1);
	close(0);
}

// the readline function after receive end of file (ctrl+d or stdin closed)
// it prints a newline by default, so here no need to add newline 
// for sigint handler after that.
void	handle_sigint_parent_without_newline(int signum)
{
	(void)signum;
	g_signal_received = 1;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// ignore the sigint for parent and make it to only print newline
// and change sigint to its default behavior in child
void	ignore_sigint_parent_in_child(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
}

// ignore sigquit for parent and make it to only print "quit"
// then change sigquit to its default behavior in child. 
void	change_behavior_sigquit_parent_in_child(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "Quit: 3\n", 8);
}
