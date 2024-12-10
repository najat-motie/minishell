
#include "../../include/minishell.h"

void	print_token(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	printf("tmp->str = %s", tmp->str);
	if(!tmp->str)
	{
		printf("NULL\n");
		return ;
	}
	printf("tmp->str : %s\n", tmp->str);
	while (tmp->next != token)
	{
		printf("Type : %d, quote : %d [%s]\n ", tmp->type,tmp->quote, tmp->str);
		tmp = tmp->next;
	}
	printf("Type : %d, quote %d [%s]\n",  tmp->type,tmp->quote, tmp->str);
}

void	print_tab(char **tab)
{
	int	i;

	if (!(tab))
	{
		printf("NULL");
		return ;
	}
	i = 0;
	printf("[");
	while (tab[i])
	{
		printf("%s", tab[i]);
		if (tab[i + 1])
			printf(", ");
		i++;
	}
	printf("]");
}

void	print_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp->next != cmd)
	{
		printf("Skip -> %d, infile -> %d, outfile -> %d, cmd : ",
		tmp->skip_cmd, tmp->infile, tmp->outfile);
		print_tab(tmp->cmd_param);
		printf("\n");
		tmp = tmp->next;
	}
	printf("Skip -> %d, infile -> %d, outfile -> %d, cmd : ", tmp->skip_cmd,
		 tmp->infile, tmp->outfile);
	print_tab(tmp->cmd_param);
	printf("\n");
}
