#include "../minishell.h"

char *add_equal(char *value)
{
    int i = 0;
    int j = 0;
    char *with_equal = malloc(ft_strlen(value) + 2);
	if(!with_equal)
		return(NULL);
	with_equal[i++] = '=';
    while(value && value[j])
        with_equal[i++] = value[j++];
    with_equal[i] = '\0';
    return(with_equal);
}

void	update_new_pwd(t_data *data)
{
	char cwd[1024];
    if(!getcwd(cwd, sizeof(cwd)))
    	perror("pwd");
	char *value = add_equal(cwd);
	update_new_pwd_env(data, value);
	update_new_pwd_export(data, value);
}

void	update_old_pwd(t_data *data)
{
	char cwd[1024];
    if(!getcwd(cwd, sizeof(cwd)))
    	perror("pwd");
	char *value = add_equal(cwd);
	update_old_pwd_env(data, value);
	update_old_pwd_export(data, value);
}	
