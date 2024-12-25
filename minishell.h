/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 22:08:52 by nmotie-           #+#    #+#             */
/*   Updated: 2024/12/24 21:11:37 by nmotie-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <sys/types.h>
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

int					g_signal_received;

# define INPUT 1 //"<"
# define HEREDOC 2 //"<<"
# define TRUNC 3 //">"
# define APPEND 4 //">>"
# define PIPE 5 //"|"
# define CMD 6 //"|"
# define ARG 7 //"|"

# define EXT_PIPE 1
# define EXT_FORK 1
# define EXT_MALLOC 1
# define ERR_MALLOC "malloc error\n"

typedef struct s_env
{
	int				equal;
	char			*key;
	char			*value;
	char			*str;
	struct s_env	*next;
}					t_env;

typedef struct s_fd
{
	int				prev_fd;
	int				read_pipe;
	int				write_pipe;
}					t_fd;

typedef struct s_cmd
{
	int				here_doc;
	int				input_fd;
	int				output_fd;
	bool			skip_cmd;
	char			**commands;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_token
{
	int				type;
	int				quote;
	char			*str;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_data
{
	int				cmd_nb;
	int				exit_status;
	t_env			*env_lst;
	t_cmd			*cmd_lst;
	t_token			*token;
	bool			sq;
	bool			dq;
}					t_data;

//quote
void				quoting_choice(bool *dq, bool *sq, int *index, char c);
int					open_quote(t_data *data, char *line);
int					exist_in_env(char *line, int *i, t_data *data);
char				*get_elem_env(t_env *env, char *key);
char				*get_dollar_word(char *line, int size);
void				quoting(bool *dq, bool *sq, char c);
int					add_dollar(char *line, int *index, char **str,
						t_data *data);
int					add_char(char *c, char **str, t_data *data, int *index);
char				*replace_dollar(char **line, t_data *data);

//token.c
bool				create_list_token(t_token **begin, char *command);
int					append_token(t_token **list, char *str, int type);

//cmd_fd.c
bool				get_infile(t_data *data, t_token *token, t_cmd *cmd);
bool				get_outfile(t_token *token, t_cmd *cmd, t_data *data);
bool				get_here_doc(t_data *data, t_token *token, t_cmd *cmd);
int					open_file(t_data *data, char *filename, int type,
						int quote);

//create_cmd.c
bool				create_list_cmd(t_data *data);
int					append_cmd(t_cmd **list, int infile, int outfile,
						char **cmd_param);
char				**get_param(t_data *data, t_token *token);
size_t				len_cmd(t_cmd *list);
bool				empty_line(char *line);
bool				parseline(t_data *data, char *line);

//utils
void				init_data(t_data *data);
size_t				len_list(t_env *list);
bool				is_true_lst_cmd(t_data *data);
bool				is_space(char c);
int					is_special(char *str);
bool				check_pipe(t_data *data);

//free.c
void				free_token(t_token **list);
void				free_array(char **arr);
bool				print_error(char *str);
void				free_all(t_data *data, char *err, int ext);
bool				print_error_token(t_token *token, t_data *data);
void				free_cmd(t_cmd **list);

// *******************************************************************

//heredoc
void				init_vars(int *i, int *j, int *n);
int					valid_dollar(char *heredoc_input, int *i);
void				replace_key_by_value(char *array, int *j, char **values,
						int *n);
int					dollar_count(char *heredoc_input);
int					key_len(char *heredoc_input, int *i);
int					values_len(char **values);
char				*get_keyname(char *heredoc_input, int *removed_count,
						int *i);
void				skip_key(char *heredoc_input, int *i);
char				*expand_input(t_data data, char *heredoc_input);
int					handle_heredoc(t_data *data, char *delimeter, int quote);

//environment
void				check_not_valid_variables(t_data *data, char **commands);
int					not_valid(char *command);
t_env				*ft_new_env(char *key, char *value, int equal, char *str);
void				add_back_env(t_env **lst, t_env *new);
void				make_env(t_data *data, char **envp);
void				export_variables(t_data *data, char **commands);
char				**get_keys(char **envp);
char				**get_value(char **envp);
void				update_new_pwd(t_data *data);
void				update_old_pwd(t_data *data);
void				unset_variables(t_data *data, char **key);
int					there_equal(char *command);

//builtins
void				get_status(t_data *data, char **commands);
int					is_nemuric(char *command);
int					is_builtin(char *command);
int					builtin_only(char **commands);
void				change_dir(t_data *data);
void				handle_exit(t_data *data, char **commands);
char				*get_pwd(void);
void				print_env(t_data *data);
void				print_export(t_data *data);
void				print_args(char **commands);
void				handle_pwd(t_data *data);
void				handle_echo(t_data *data, char **commands);
void				handle_cd(t_data *data);
void				handle_export(t_data *data, char **commands);
void				handle_unset(t_data *data, char **commands);
void				handle_builtins(t_data *data, char **commands);

//signals
void				handle_sigint_parent(int signum);
void				handle_sigint_parent_in_heredoc(int sig);
void				handle_sigint_parent_without_newline(int signum);
void				ignore_sigint_parent_in_child(int sig);
void				change_behavior_sigquit_parent_in_child(int signum);
void				handle_end_of_file(void);
void				catch_signals(void);

//execute
void				set_input_and_output(t_cmd *tmp, t_fd *fd);
void				set_read_write_pipe(t_data data, t_cmd *tmp, t_fd *fd,
						int i);
void				save_read_of_pipe(t_data data, t_fd *fd, int i);
char				*retreive_value(t_data data, char *key);
char				*get_path(t_data data, char *command);
void				check_path(char *path, char *command);
void				wait_pids(t_data *data, int *pids);
int					create_pipe(t_data *data, t_fd *fd_, int i);
void				excute_commands(t_data *data);
int					commands_numbr(t_data data);
void				clear_ressources(int *pid, t_fd *fd, int *i);
int					move_to_next_cmd(t_data data, t_cmd **tmp, int *i);

//free
void				ft_free(char **s);
void				clear_env(t_env **lst);

#endif
