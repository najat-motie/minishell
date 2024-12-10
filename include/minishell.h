
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../Libft/libft.h"

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


typedef struct s_cmd
{
	bool			skip_cmd;
	int				infile;
	int				outfile;
	char			**cmd_param;
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

typedef struct s_list
{
	char			*str;
	struct s_list	*prev;
	struct s_list	*next;
}					t_list;

typedef struct s_data
{
	t_list	*env;
	t_token	*token;
	t_cmd	*cmd;
	int		exit_code;
	bool	sq;
}				t_data;

/* main */
int		make_env(t_data *data, char **env);

int    handle_heredoc(t_data *data, char *delimeter,int *quote);
/* List utils */
int		free_list(t_list **list);
int		append(t_list **list, char *elem);
size_t	len_list(t_list *list);

/* quote */
void	quoting_choice(bool *dq, bool *sq, int *index, char c);
int		open_quote(t_data *data, char *line);
int		exist_in_env(char *line, int *i, t_data *data);
char	*get_elem_env(t_list *env, char *key);
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

#endif
