/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:34:00 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/19 17:45:09 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	catch_signals(void)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("signal");
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
		perror("signal");
}

void	handle_end_of_file(void)
{
	printf("exit\n");
	exit(EXIT_SUCCESS);
}
