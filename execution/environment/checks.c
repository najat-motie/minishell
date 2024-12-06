#include "../minishell.h"

int check_other_characters(char *command)
{
	int j = 1;

	while(command[j] && command[j] != '=')
	{
		if ((command[j] < 'a' || command[j] > 'z')
			&& (command[j] < 'A' || command[j] > 'Z')
			&& (command[j] < '0' || command[j] > '9')
			&& command[j] != '_')
			return(1);
		j++;
	}
	return(0);
}

int	not_valid(char *command)
{
	if ((command[0] < 'a' || command[0] > 'z')
		&& (command[0] < 'A' || command[0] > 'Z')
		&& command[0] != '_')
		return(1);
	if (check_other_characters(command))
		return(1);
	return(0);
}

void	check_not_valid_variables(t_data *data, char **commands)
{
	int	i;

	i = 1;
	while (commands[i])
	{
        if ((commands[i][0] < 'a' || commands[i][0] > 'z')
			&& (commands[i][0] < 'A' || commands[i][0] > 'Z')
			&& commands[i][0] != '_')
		{
			printf("minishell: %s: `%s': not a valid identifier\n", commands[0], commands[i]);
            data->exit_status = 1;
		}
		else if (check_other_characters(commands[i]))
        {
			printf("minishell: %s: `%s': not a valid identifier\n", commands[0], commands[i]);
            data->exit_status = 1;
        }
		i++;
	}
}
