#ifndef MINISHELL_H
# define MINISHELL_H

int signal_received;

typedef struct s_env
{
    // char *content;
    char *key;
    char *value;
    int equal;
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
    int cmd_nb;
    char *input;
    char **envp;
    t_env *env_lst;
    t_cmd *cmd_lst;
}   t_data;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#include "./libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

//builtins
int is_builtin(char *command);
int builtin_only(char **commands);
void    change_dir(t_data *data);
char *get_pwd();
void    print_env(t_data *data);
void    print_export(t_data *data);
void    echo_printing(char **commands);
void    handle_pwd(t_data *data);
void    handle_echo(t_data *data, char **commands);
void handle_cd(t_data *data);
void    handle_export(t_data *data, char **commands);
void    handle_unset(t_data *data, char **commands);
void handle_builtins(t_data *data, char **commands);

//envirenmet
t_env	*ft_new_env(char *key, char *value, int equal);
void	add_back_env(t_env **lst, t_env *new);
void    fill_env_lst(t_data *data);
int  not_valid_export(char **commands);
void	export_commands(t_data *data, char **commands);
char **get_keys(char **envp);
char **get_value(char **envp);
void	update_new_pwd(t_data *data);
void	update_old_pwd(t_data *data);
int  not_valid_unset(char **commands);
void    unset_commands(t_data *data, char **key);
int there_equal(char *command);

//signals
void    handle_eof(t_data data);
void    sigint_parent(int signum);
void    sigint_heredoc(int sig);
void    sigint_child(int sig);
void    sigint_parent_without_newline(int signum);

//redirections
char    *expand_input(t_data data, char *heredoc_input);
char *retreive_value(t_data data, char *key);
int    redirect_output(char *file_name);
int    redirect_input(char *file_name);
int    redirect_append(char *file_name);
int    handle_heredoc(t_data *data, char *delimeter);
void    handle_redirects(t_data *data);

//execute
void ft_free(char **str);
char *get_path(t_data, char *command);
void    excute_cmnds(t_data *data);
void    fill_cmd_lst(t_data *data);

# endif