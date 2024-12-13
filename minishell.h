
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <fcntl.h>
#include <signal.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

int signal_received;

# define INPUT		1	//"<"
# define HEREDOC	2	//"<<"
# define TRUNC		3	//">"
# define APPEND		4	//">>"
# define PIPE		5	//"|"
# define CMD		6	//"|"
# define ARG		7	//"|"

# define ERR_MALLOC	"malloc error\n"
# define ERR_PIPE	"pipe error\n"
# define ERR_FORK	"fork error\n"

# define EXT_MALLOC	1
# define EXT_PIPE	1
# define EXT_FORK	1

typedef struct s_env
{
    char *key;
    char *value;
    int equal;
	char *str;
    struct s_env *next;
}   t_env;

typedef struct s_fd
{
    int prev_fd;
    int read_pipe;
    int write_pipe;
} t_fd;

typedef struct s_cmd
{
	int 			input_fd;
    int 			output_fd;
	bool			skip_cmd;
	char			**commands;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_token
{
	char			*str;
	int				type;
	int				quote;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

// typedef struct s_list
// {
// 	char			*str;
// 	struct s_list	*prev;
// 	struct s_list	*next;
// }					t_list;

typedef struct s_data
{
	// char **envp;
	// t_env	*env;
	t_token	*token;
	t_cmd	*cmd_lst;
    t_env *env_lst;
	int		exit_status;
	int cmd_nb;
	bool	sq;
}				t_data;

/* main */
// int		make_env(t_data *data, char **env);

int    handle_heredoc(t_data *data, char *delimeter,int *quote);
/* List utils */
int		free_list(t_env **list);
int		append(t_env **list, char *elem);
size_t	len_list(t_env *list);

/* quote */
void	quoting_choice(bool *dq, bool *sq, int *index, char c);
int		open_quote(t_data *data, char *line);
int		exist_in_env(char *line, int *i, t_data *data);
char	*get_elem_env(t_env *env, char *key);
char	*get_dollar_word(char *line, int size);

int		add_dollar(char *line, int *index, char **str, t_data *data);
int		add_char(char *c, char **str, t_data *data, int *index);
int		replace_dollar(char **line, t_data *data);


//create_token.c
bool	create_list_token(t_token **begin, char *command);

//list_token.c
int		append_token(t_token **list, char *str, int type);
void	free_token(t_token **list);

//ms_utils.c
bool	is_space(char c);
int		is_special(char *str);
bool	check_pipe(t_data *data);

//free.c
void	free_array(char **arr);
bool	print_error(char *str);
void	free_all(t_data *data, char *err, int ext);
bool	print_error_token(t_token *token, t_data *data);


//list_cmd.c
int		append_cmd(t_cmd **list, int infile, int outfile, char **cmd_param);
void	free_cmd(t_cmd **list);
size_t	len_cmd(t_cmd *list);

//create_cmd.c
bool	create_list_cmd(t_data *data);

//cmd_fd.c
bool	get_infile(t_data *data, t_token *token, t_cmd *cmd);
bool	get_outfile(t_token *token, t_cmd *cmd, t_data *data);

//here_doc.c
int		here_doc(t_data *data, char *word);

//cmd_param.c
char	**get_param(t_data *data, t_token *token);




// ********        DEBUG        ********** //
void	print_token(t_token *token);
void	print_tab(char **tab);
void	print_cmd(t_cmd *cmd);


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
t_env	*ft_new_env(char *key, char *value, int equal, char *str);
void	add_back_env(t_env **lst, t_env *new);
void    make_env(t_data *data, char **envp);
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
// int    handle_heredoc(t_data *data, char *delimeter);
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
int	create_pipe(t_data *data, t_fd *fd_, int i);
void	excute_commands(t_data *data);

//other
void    ft_free(char **s);
// void    fill_cmd_lst(t_data *data);
void	clear_env(t_env **lst);
// void	lstclear_cmd(t_cmd **lst);
// char **get_commands(char **str);
// char **get_types(char **cmnds);
// char **get_files(char **cmnds, int *not_quouted);

#endif
