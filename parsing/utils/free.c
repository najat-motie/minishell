#include "../../minishell.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	if (arr)
		free(arr);
	arr = NULL;
}

bool	print_error(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	return (true);
}

bool	print_error_token(t_token *token, t_data *data)
{
	write(2, "syntax error near unexpected token ", 35);
	write(2, "'", 1);
	if (token->next == data->token)
		write(2, "newline", 7);
	else
		write(2, token->next->str, ft_strlen(token->next->str));
	write(2, "'\n", 2);
	return (false);
}

void	free_all(t_data *data, char *err, int ext)
{
	if (data->cmd_lst)
		free_cmd(&data->cmd_lst);
	if (data->token)
		free_token(&data->token);
	if (data->env_lst)
		free_list(&data->env_lst);
	if (err)
		print_error(err);
	if (ext != -1)
		exit(ext);
}
