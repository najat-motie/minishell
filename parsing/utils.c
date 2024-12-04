#include "../minishell.h"

char **get_commands(char **str)
{
    int i = 0;
	int j = 0;
	int k = 0;
	while(str[i] && (ft_strcmp(str[i], ">") != 0 && ft_strcmp(str[i], ">>") != 0 
        && ft_strcmp(str[i], "<") != 0 && ft_strcmp(str[i], "<<") != 0))
	{
		i++;
		j++;
	}
    char **commands = malloc((j + 1) * sizeof(char *));
	i = 0;
    while (k < j)
        commands[k++] = str[i++];
    commands[k] = NULL;
    return(commands);
}

int number_redirects(char **command)
{
	int count = 0;
	int i = 0;
	while(command[i])
	{
		if(ft_strcmp(command[i], ">") == 0 || ft_strcmp(command[i], ">>") == 0 || ft_strcmp(command[i], "<") == 0 || ft_strcmp(command[i], "<<") == 0)
			count++;
		i++;
	}
	return(count);
}

char **get_types(char **cmnds)
{
	int i = 0;
	int count = number_redirects(cmnds);
	char **all_types = malloc((count + 1) * sizeof(char *));
	int j = 0;
	while(cmnds[i])
	{
		if(ft_strcmp(cmnds[i], "<") == 0 || ft_strcmp(cmnds[i], "<<") == 0 
			|| ft_strcmp(cmnds[i], ">") == 0 || ft_strcmp(cmnds[i], ">>") == 0)
		{
			int k = 0;
			while(cmnds[i][k] != ' ' && cmnds[i][k] != '\0')
				k++;
			all_types[j] = malloc(k + 1);
			k = 0;
			while(cmnds[i][k])
			{
				all_types[j][k] = cmnds[i][k];
				k++;
			}
			all_types[j][k] = '\0';
			j++;
		}
		i++;
	}
	all_types[j] = NULL;
	return(all_types);
}


char **get_files(char **cmnds, int *not_quouted)
{
	int i = 0;
	int count = number_redirects(cmnds);
	char **all_files = malloc((count + 1) * sizeof(char *));
	int l = 0;
	while(cmnds[i])
	{
		if(ft_strcmp(cmnds[i], "<") == 0 || ft_strcmp(cmnds[i], "<<") == 0 
			|| ft_strcmp(cmnds[i], ">") == 0 || ft_strcmp(cmnds[i], ">>") == 0)
		{
			if(ft_strcmp(cmnds[i], "<<") == 0)
			{
				int x = i;
				int y = 0;
				x++;
				if(cmnds[x][y] == '"' || cmnds[x][y] == '\'')
				{
					y++;
					while(cmnds[x][y] != '"' && cmnds[x][y] == '\'' && cmnds[x][y] != '\0')
						y++;
					if(cmnds[x][y] == '"' || cmnds[x][y] == '\'')
						*not_quouted = 0;
				}
			}
			int j = i;
			j++;
			int k = 0;
			while(cmnds[j][k] != ' ' && cmnds[j][k])
				k++;
			all_files[l] = malloc(k + 1);
			k = 0;
			while(cmnds[j][k])
			{
				all_files[l][k] = cmnds[j][k];
				k++;
			}
			all_files[l][k] = '\0';
			l++;
		}
		i++;
	}
	all_files[l] = NULL;
	return(all_files);
}
