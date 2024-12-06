#include "../minishell.h"

char *retreive_value(t_data data, char *key)
{
    t_env *env_tmp = data.env_lst;

    while(env_tmp)
    {
        if(ft_strcmp(env_tmp->key, key) == 0)
            return(env_tmp->value);           
        env_tmp = env_tmp->next;
    }
    return(NULL);
}

char	*check_current_working_directory(char *command)
{
	char	*path;
	char	*pwd;

	pwd = get_pwd();
	if (!pwd)
	{
		perror("getcwd");
		return (NULL);
	}
	path = ft_strjoin(ft_strjoin(pwd, "/"), command);
	if (access(path, X_OK) == 0)
		return (path);
	else
	{
		perror(command);
		return (NULL);
	}
}

char	*get_path_of_command(t_data data, char *command)
{
	int		i;
	char	*path;
	char	*full_path;
	char	**all_paths;

	path = retreive_value(data, "PATH");
	if (path == NULL)
	{
		path = check_current_working_directory(command);
		if (path)
			return (path);
		return (NULL);
	}
	i = 0;
	all_paths = ft_split(path, ':');
	while (all_paths != NULL && all_paths[i] != NULL)
	{
		full_path = ft_strjoin(ft_strjoin(all_paths[i], "/"), command);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		i++;
	}
	return ("not valid command");
}

char	*get_path(t_data data, char *command)
{
	if (!command)
		return (NULL);
	if (ft_strchr(command, '/') != NULL || ft_strchr(command, '.') != NULL)
	{
		if (access(command, X_OK) == 0)
			return (command);
		else
		{
			perror(command);
			return (NULL);
		}
	}
	return (get_path_of_command(data, command));
}

void	check_path(char *path, char *command)
{
	if (ft_strcmp(path, "not valid command") == 0)
	{
		printf("minishell: %s: command not found\n", command);
		exit(127);
	}
	else if (!path && command)
		exit(127);
	else if (!path && !command)
		exit(EXIT_SUCCESS);
}
