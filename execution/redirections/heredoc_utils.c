#include "../../minishell.h"

int dollar_count(char *heredoc_input)
{
    int i = 0;
    int count = 0;
    while(heredoc_input[i])
    {
        if(heredoc_input[i] == '$' && ((heredoc_input[i + 1] >= 'a' && heredoc_input[i + 1] <= 'z') || (heredoc_input[i + 1] >= 'A' && heredoc_input[i + 1] <= 'Z') || (heredoc_input[i + 1] == '_')))
            count++;
        i++;
    }
    return(count);
}

char    *expand_input(t_data data, char *heredoc_input)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    int n = 0;
    char *to_expand = NULL;
    int removed_count = 0;
    int dollar = dollar_count(heredoc_input);
    char **expanded = malloc((dollar + 1) * sizeof(char *));
    if(expanded == NULL)
    {
        perror("malloc");
        return(NULL);
    }
    while(heredoc_input[i])
    {
        if(heredoc_input[i] == '$')
        {
            if((heredoc_input[i + 1] >= 'a' && heredoc_input[i + 1] <= 'z') || (heredoc_input[i + 1] >= 'A' && heredoc_input[i + 1] <= 'Z') || (heredoc_input[i + 1] == '_'))
            {
                i++;
                removed_count++;
                k = 0;
                l = i;
                while((heredoc_input[l] >= 'a' && heredoc_input[l] <= 'z') || (heredoc_input[l] >= 'A' && heredoc_input[l] <= 'Z') || (heredoc_input[l] >= '0' && heredoc_input[l] <= '9') || (heredoc_input[l] == '_'))
                {
                    l++;
                    k++;
                }
                to_expand = malloc(k + 1);
                if(to_expand == NULL)
                {
                    perror("malloc");
                    return(NULL);
                }
                k = 0;
                while((heredoc_input[i] >= 'a' && heredoc_input[i] <= 'z') || (heredoc_input[i] >= 'A' && heredoc_input[i] <= 'Z') || (heredoc_input[i] >= '0' && heredoc_input[i] <= '9') || (heredoc_input[i] == '_'))
                    to_expand[k++] = heredoc_input[i++];
                i--;
                to_expand[k] = '\0';
                expanded[n++] = retreive_value(data, to_expand);
            }
        }
        i++;
    }
    expanded[n] = NULL;
    n = 0;
    int count = 0;
    while(expanded[n])
    {
        count += ft_strlen(expanded[n]);
        n++;
    }
    char *input = malloc(ft_strlen(heredoc_input) - ft_strlen(to_expand) - removed_count + count + 1);
    if(!input)
    {
        perror("malloc");
        return(NULL);
    }
    i = 0;
    j = 0;
    k = 0;
    l = 0;
    n = 0;
    while(heredoc_input[i])
    {
        while(heredoc_input[i] && heredoc_input[i] != '$')
            input[j++] = heredoc_input[i++];
        if(heredoc_input[i] == '$')
        {
            l = i;
            if((heredoc_input[l + 1] >= 'a' && heredoc_input[l + 1] <= 'z') || (heredoc_input[l + 1] >= 'A' && heredoc_input[l + 1] <= 'Z') || (heredoc_input[l + 1] == '_'))
            {
                l++;
                k = 0;
                while(expanded[n] && expanded[n][k])
                    input[j++] = expanded[n][k++];
                while((heredoc_input[l] >= 'a' && heredoc_input[l] <= 'z') || (heredoc_input[l] >= 'A' && heredoc_input[l] <= 'Z') || (heredoc_input[l] >= '0' && heredoc_input[l] <= '9') || (heredoc_input[l] == '_'))
                    l++;
                i = l;
                n++;
            }
            else
                input[j++] = heredoc_input[i];   
        }
    }
    input[j] = '\0';
    return(input);
}
