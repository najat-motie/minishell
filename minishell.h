#ifndef MINISHELL_H
# define MINISHELL_H

int received_signal;

typedef struct s_env
{
    char *content;
    char *key;
    char *value;
    struct s_env *next;
}   t_env;

typedef struct s_red
{
    char *file_name;
    int not_quouted;
    char *symbol_type;
    struct s_red *next;  
}   t_red;

typedef struct s_cmd
{
    int fd_input;
    int fd_output;
    int fd_heredoc;
    char **commands; 
    t_red *red_lst;
    struct s_cmd *next;
}   t_cmd;

typedef struct s_data
{
    int exit_status;
    char *input;
    char **envp;
    t_env *env_lst;
    t_env *export_lst;
    int cmd_nb;
    t_cmd *cmd_lst;
}   t_data;

#include <termios.h>
#include <signal.h>
#include <stdio.h>
#include "./libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

void disable_echo_ctrl();
void    handle_eof(t_data data);
void    handle_sigint_child_process(int signum);
char    *expand_input(t_data data, char *heredoc_input);
int    handle_heredoc(t_data data, char *delimeter);
int	ft_strcmp(char *s1, char *s2);
void ft_free(char **str);
t_env	*ft_newnode(char *content, char *key, char *value);
void	add_back(t_env **lst, t_env *new);
int is_quouted(char *value);
int  not_valid_export(char **commands);
int  not_valid_unset(char **commands);
void    unset_commands(t_data *data, char **key);
void	export_commands(t_data *data, char **commands);      
char **get_keys(char **envp);
char **get_value(char **envp);
void	add_to_export_lst(t_data *data, char *key, char *value, char *command);
void	add_to_env_export(t_data *data, char *key, char *value, char *command);
void	update_old_pwd(t_data *data);
void	update_new_pwd(t_data *data);
int is_builtin(char *command);
int builtin_only(char **commands);
char *retreive_value(t_data data, char *key);
void builtin_commands(t_data *data, char **commands);
void    print_env(t_data data);
void    print_export(t_data data);
int    redirect_output(char *file_name);
int    redirect_input(char *file_name);
int    redirect_append(char *file_name);
int    handle_heredoc(t_data data, char *delimeter);
char *get_path(t_data, char *command);
void    excute_cmnds(t_data *data);
void    fill_env_lst(t_data *data);
void    fill_export_lst(t_data *data);
void    fill_cmd_lst(t_data *data);
void    handle_redirects(t_data *data);
void    handle_sigint(int signum);

# endif