/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ner-roui <ner-roui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:48:47 by ner-roui          #+#    #+#             */
/*   Updated: 2024/12/23 15:52:41 by ner-roui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_data(t_data *data)
{
	data->token = NULL;
	data->env_lst = NULL;
	data->cmd_lst = NULL;
	data->exit_status = 0;
}