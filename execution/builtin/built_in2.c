#include "../../minishell.h"

void    print_env(t_data *data)
{
    t_env *tmp_lst = data->env_lst;
    
	while(tmp_lst)
	{
		printf("%s", tmp_lst->key);
        // printf("-->here\n");
        if(tmp_lst->value)
		    printf("=%s\n", tmp_lst->value);
        else
            printf("\n");
		tmp_lst = tmp_lst->next;
    }
    data->exit_status = 0;
}

void    print_export(t_data *data)
{
   t_env *tmp_lst = data->env_lst;

	while(tmp_lst)
	{
		printf("declare -x ");
		printf("%s", tmp_lst->key);
        if(tmp_lst->equal)
        {
            printf("=\"");
            if(tmp_lst->value != NULL)
                printf("%s", tmp_lst->value);
            printf("\"");
        }
        printf("\n");
        tmp_lst = tmp_lst->next;
    }
    data->exit_status = 0;
}

void    handle_export(t_data *data, char **commands)
{
    export_variables(data, commands);
    data->exit_status = 0;
    check_not_valid_variables(data, commands);
}

void    handle_unset(t_data *data, char **commands)
{
    unset_variables(data, commands);
    data->exit_status = 0;
    check_not_valid_variables(data, commands);
}
