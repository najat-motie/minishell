#include "../minishell.h"

int no_quoutes(char *value)
{
    int i = 0;

    while(value && value[i])
    {
        if(value[i] == '"')
            return(0);
        i++;
    }
    return(1);
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
            printf("=");
            if(no_quoutes(tmp_lst->value)) // the parsing already should remove those quoutes
                printf("\"");
            if(tmp_lst->value != NULL)
                printf("%s", tmp_lst->value);
            if(no_quoutes(tmp_lst->value))
                printf("\"");
        }
        printf("\n");
        tmp_lst = tmp_lst->next;
    }
    data->exit_status = 0;
}

int there_dollar(char *command)
{
    int i = 0;
    while(command[i])
    {
        if(command[i] == '$')
            return(1);
        i++;
    }
    return(0);
}

void    expand_dollar(t_data data, char *command)
{
    int j = 0;

    while(command[j])
    {
        while(command[j] && command[j] != '$')
        {
            printf("%c", command[j]);
            j++;
        }
        if(command[j] == '$' && command[j + 1] == '?')
        {
            printf("%d", data.exit_status);
            j += 2;
        }
        else if(command[j] == '$' && command[j + 1] != '?')
        {
            while(command[j] && command[j] != ' ')
                j++;
        }
    }
    //single quoute and double quoute handled from parsing
}
