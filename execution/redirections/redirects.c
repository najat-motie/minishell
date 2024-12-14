/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:23:04 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/14 16:23:05 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    heredoc_redirects(t_data *data)
{ 
    t_cmd *tmp_cmd;
    t_token *tmp_token;

    tmp_cmd = data->cmd_lst;
    while(!signal_received)
    {
        tmp_token = data->token;
        while(!signal_received)
        {
            if(tmp_token->type == HEREDOC)
            {
                close(tmp_cmd->heredoc_fd);
                tmp_cmd->heredoc_fd = handle_heredoc(data, tmp_token->next->str, tmp_token->next->quote);
            }
            tmp_token = tmp_token->next;
            if(tmp_token->type == PIPE || tmp_token == data->token)
                break;
        }
        tmp_cmd = tmp_cmd->next;
        if(tmp_cmd == data->cmd_lst)
            break;
    }
}

void    input_redirects(t_data *data)
{
    t_cmd *tmp_cmd;
    t_token *tmp_token;

    tmp_cmd = data->cmd_lst;
    while(!signal_received)
    {
        tmp_token = data->token;
        while(!signal_received)
        {
            if(tmp_cmd->input_fd == -1 || tmp_cmd->output_fd == -1)
                break ;
            if(tmp_token->type == INPUT)
            {
                close(tmp_cmd->input_fd);
                tmp_cmd->input_fd = redirect_input(tmp_token->next->str);
            }
            if(tmp_token->type == HEREDOC)
            {
                close(tmp_cmd->input_fd);
                tmp_cmd->input_fd = tmp_cmd->heredoc_fd;
            }
            tmp_token = tmp_token->next;
            if(tmp_token->type == PIPE || tmp_token == data->token)
                break;
        }
        tmp_cmd = tmp_cmd->next;
        if(tmp_cmd == data->cmd_lst)
            break;
    }
}

void    output_redirects(t_data *data)
{
    t_cmd *tmp_cmd;
    t_token *tmp_token;

    tmp_cmd = data->cmd_lst;
    while(!signal_received)
    {
        tmp_token = data->token;
        while(!signal_received)
        {
            if(tmp_cmd->input_fd == -1 || tmp_cmd->output_fd == -1)
                break ;
            if(tmp_token->type == TRUNC)
            {
                close(tmp_cmd->output_fd);
                tmp_cmd->output_fd = redirect_output(tmp_token->next->str);
            }
            if(tmp_token->type == APPEND)
            {
                close(tmp_cmd->output_fd);
                tmp_cmd->output_fd = redirect_append(tmp_token->next->str);
            }
            tmp_token = tmp_token->next;
            if(tmp_token->type == PIPE || tmp_token == data->token)
                break;
        }
        tmp_cmd = tmp_cmd->next;
        if(tmp_cmd == data->cmd_lst)
            break;
    }
}

void    handle_redirects(t_data *data)
{
    // data->cmd_lst->input_fd = -2;
    // data->cmd_lst->output_fd = -2;
    heredoc_redirects(data);
    input_redirects(data);
    output_redirects(data);
}