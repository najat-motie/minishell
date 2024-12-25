/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:34:00 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/24 11:08:55 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// ignore sigquit signal
// change behavior of sigint signal
void	catch_signals(void)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("signal");
	if (signal(SIGINT, handle_sigint_parent) == SIG_ERR)
		perror("signal");
}

// when ctrl+d received
void	handle_end_of_file(void)
{
	printf("exit\n");
	exit(EXIT_SUCCESS);
}
