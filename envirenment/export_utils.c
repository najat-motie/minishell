#include "../minishell.h"

int is_quouted(char *value)
{
	int i = 0;
	if(!value)
		return(0);
	while(value[i])
	{
		if(value[i] == '=')
		{
			i++;
			if(value[i] == '"')
			{
				i++;
				while(value[i] != '"' && value[i] != '\0')
					i++;
				if(value[i] == '"')
					return(1);
			}
		}
	}
	return(0);
}

char *add_quoutes(char *key, char *value)
{
	char *cmnd = malloc(ft_strlen(key) + ft_strlen(value) + 3);
	if(cmnd == NULL)
		return(NULL);
	int i = 0;
	while(key[i] && key[i] != '=')
	{
		cmnd[i] = key[i];
		i++;
	}
	int j = 0;
	if(value && value[j] == '=')
	{
		cmnd[i++] = '=';
		cmnd[i++] = '"';
		j++;
		while(value[j])
		{
			cmnd[i] = value[j];
			i++;
			j++;
		}
		cmnd[i++] = '"';
	}
	cmnd[i] = '\0';
	return(cmnd);
}
