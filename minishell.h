#ifndef MINISHELL_H
# define MINISHELL_H

int signal_received;

typedef struct s_env
{
    char *key;
    char *value;
    int equal;
    struct s_env *next;
}   t_env;

typedef struct s_red
{
    char *file_name;
    char *symbol_type;
    int not_quouted;
    struct s_red *next;  
}   t_red;

typedef struct s_fd
{
    int prev_fd;
    int read_pipe;
    int write_pipe;
} t_fd;

typedef struct s_cmd
{
    int heredoc_fd;
    int input_fd;
    int output_fd;
    int *numberes;
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

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
 #include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "execution/libft/libft.h"

//builtins
int there_dollar(char *command);
void    get_status(char **commands);
void    expand_dollar(t_data data, char *command);
int is_nemuric(char *command);
int is_builtin(char *command);
int builtin_only(char **commands);
void    change_dir(t_data *data);
void    handle_exit(char **commands);
char *get_pwd();
void    print_env(t_data *data);
void    print_export(t_data *data);
void    echo_printing(t_data data, char **commands);
void    handle_pwd(t_data *data);
void    handle_echo(t_data *data, char **commands);
void handle_cd(t_data *data);
void    handle_export(t_data *data, char **commands);
void    handle_unset(t_data *data, char **commands);
void handle_builtins(t_data *data, char **commands);

//environment
void	check_not_valid_variables(t_data *data, char **commands);
int	not_valid(char *command);
t_env	*ft_new_env(char *key, char *value, int equal);
void	add_back_env(t_env **lst, t_env *new);
void    fill_lst(t_data *data);
void	export_variables(t_data *data, char **commands);
char **get_keys(char **envp);
char **get_value(char **envp);
void	update_new_pwd(t_data *data);
void	update_old_pwd(t_data *data);
void    unset_variables(t_data *data, char **key);
int there_equal(char *command);

//redirections
void	init_vars(int *i, int *j, int *n);
int valid_dollar(char *heredoc_input, int *i);
void	replace_key_by_value(char *array, int *j, char **values, int *n);
int	dollar_count(char *heredoc_input);
int	key_len(char *heredoc_input, int *i);
int	values_len(char **values);
char	*get_keyname(char *heredoc_input, int *removed_count, int *i);
void	skip_key(char *heredoc_input, int *i);
char    *expand_input(t_data data, char *heredoc_input);
int    handle_heredoc(t_data *data, char *delimeter);
int    redirect_output(char *file_name);
int    redirect_input(char *file_name);
int    redirect_append(char *file_name);
void    handle_redirects(t_data *data);

//signals
void    sigint_parent(int signum);
void    sigint_heredoc(int sig);
void    sigint_child(int sig);
void    sigint_parent_without_newline(int signum);
void    sigquit_child(int signum);

//execute
void	set_input_and_output(t_data data, t_fd fd);
void	set_read_write_pipe(t_data data, t_fd fd, int i);
void	save_read_of_pipe(t_data data, t_fd *fd, int i);
char *retreive_value(t_data data, char *key);
char	*get_path(t_data data, char *command);
void	check_path(char *path, char *command);
void	wait_pids(t_data *data, int *pids);
int	create_pipe(t_data *data, int fd[], t_fd *fd_, int i);
void	excute_commands(t_data *data);

//other
void    ft_free(char **s);
void    fill_cmd_lst(t_data *data);
void	lstclear_env(t_env **lst);
void	lstclear_cmd(t_cmd **lst);
char **get_commands(char **str);
char **get_types(char **cmnds);
char **get_files(char **cmnds, int *not_quouted);

# endif