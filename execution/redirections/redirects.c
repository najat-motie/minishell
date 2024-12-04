#include "../../minishell.h"

void    heredoc_redirects(t_data *data)
{ 
    t_cmd *tmp_cmd;
    t_red *tmp_red;

    tmp_cmd = data->cmd_lst;
    while(tmp_cmd && !signal_received)
    {
        tmp_red = tmp_cmd->red_lst;
        while(tmp_red && !signal_received)
        {
            if(ft_strcmp(tmp_red->symbol_type, "<<") == 0)
            {
                close(tmp_cmd->heredoc_fd);
                tmp_cmd->heredoc_fd = handle_heredoc(data, tmp_red->file_name);
            }
            tmp_red = tmp_red->next;
        }
        tmp_cmd = tmp_cmd->next;
    }
}

void    input_redirects(t_data *data)
{
    t_cmd *tmp_cmd;
    t_red *tmp_red;

    tmp_cmd = data->cmd_lst;
    while(tmp_cmd && !signal_received)
    {
        tmp_red = tmp_cmd->red_lst;
        while(tmp_red && !signal_received)
        {
            if(tmp_cmd->input_fd == -2 || tmp_cmd->output_fd == -2)
                break ;
            if(ft_strcmp(tmp_red->symbol_type, "<") == 0)
            {
                close(tmp_cmd->input_fd);
                tmp_cmd->input_fd = redirect_input(tmp_red->file_name);
            }
            if(ft_strcmp(tmp_red->symbol_type, "<<") == 0)
            {
                close(tmp_cmd->input_fd);
                tmp_cmd->input_fd = tmp_cmd->heredoc_fd;
            }
            tmp_red = tmp_red->next;
        }
        tmp_cmd = tmp_cmd->next;
    }
}

void    output_redirects(t_data *data)
{
    t_cmd *tmp_cmd;
    t_red *tmp_red;

    tmp_cmd = data->cmd_lst;
    while(tmp_cmd && !signal_received)
    {
        tmp_red = tmp_cmd->red_lst;
        while(tmp_red && !signal_received)
        {
            if(tmp_cmd->input_fd == -2 || tmp_cmd->output_fd == -2)
                break ;
            if(ft_strcmp(tmp_red->symbol_type, ">") == 0)
            {
                close(tmp_cmd->output_fd);
                tmp_cmd->output_fd = redirect_output(tmp_red->file_name);
            }
            if(ft_strcmp(tmp_red->symbol_type, ">>") == 0)
            {
                close(tmp_cmd->output_fd);
                tmp_cmd->output_fd = redirect_append(tmp_red->file_name);
            }
            tmp_red = tmp_red->next;
        }
        tmp_cmd = tmp_cmd->next;
    }
}

void    handle_redirects(t_data *data)
{
    heredoc_redirects(data);
    input_redirects(data);
    output_redirects(data);
}
