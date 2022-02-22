/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:41:28 by acollin           #+#    #+#             */
/*   Updated: 2021/10/06 20:42:12 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <limits.h>

// TOKEN types
# define CMD				11
# define	REDIR			22
# define REDIR_APPEND	23
# define REDIR_INPUT		24
# define HERE_DOC		25
# define PIPE			44
# define ENV				55

// Delimeters:
# define DELIM	" \t"

# define DELETE_MID	7
# define MID			8

// Executor:
# define MALLOC_ERR	1
# define FORK_ERR	2
# define MAX_DIRNAME 4096
# define MAX_FILENAME 255

typedef struct s_tlist	t_tlist;
typedef struct s_btree	t_btree;

// Lexer linked list of tokens:
struct			s_tlist
{
	int 		type;
	char 		*infile;
	char 		*outfile;
	char		**cmd;
	char 		*args;
	t_tlist		*next;
};

// AST
struct 			s_btree
{
	char 		**value;
	int 		type;
	char 		**args;
	t_btree		*left;
	t_btree		*right;
};

//Executor:
typedef struct	s_cmd
{
	char	*cmd;
	int		(*f_cmd)(char **args, t_list **var_list);
}				t_cmd;

typedef struct s_vlist
{
	struct s_var	*content;
	struct s_vlist	*next;
}					t_vlist;

typedef struct	s_var //для хранения переменных окружения и переменных среды
{
	char		*name;
	char		*value;
	int 		is_exported; //0 - переменная среды, 1 - переменная окружения
}					t_var;

// Preparsing
char	*preparse(char *prompt);
int		unmatched_quotes(char *prompt, int i);
void	preparse_quotes(char const *prompt, int *i);
char	*preparse_delim(char *prompt, int i);
int		preparse_redir(char *prompt, int i);
int		preparse_pipe(char *prompt, int i);

// Preparsing utils
char	*str_delete_part(char *prompt, int start, int end, int flag_mid);

// LEXER:
void	init_lexer(t_tlist *token);
char	*dollar_string(char *tmp, t_list **var_list);
char	**ft_quotes_split(char const *str, char c);
void	*ft_quotes_abort(char ***arr, int size);
int 	get_quotes_len(char *str, char c, int *i);
int 	get_quotes_arrlen(char const *s, char c);
char	**get_quotes_str(char ***res, char **str, char c, int size);
void	lexer(char *prompt, t_tlist **tokens, t_list **var_list);
char	*lexer_quotes(char *prompt, int *i, t_list **var_list);
char	*lexer_dollar(char *prompt, int *i, t_list **var_list);
char	*lexer_redir(t_tlist **tokens, char *prompt, int i);
void	lexer_cmd(t_tlist **tokens, char *prompt);
char	*lexer_pipe(t_tlist **tokens, int *i, char *tmp);

// Parsing
t_btree	*parse_line(t_tlist *tokens);
t_btree	*btreenew(int type);
t_tlist	*left_lst(t_tlist *tokens, int i);
t_tlist	*right_lst(t_tlist *tokens);
t_btree	*build_ast(t_tlist *tokens);

//void	free_node_tree(t_btree *node);
void	clear_ast(t_btree *ast);

// MAYBE DELETE LATER... IDK
char	*ft_quotes(char *prompt, int *i);
char	*ft_doublequotes(char *prompt, int *i);
char	*ft_dollar(char *prompt, int *i, char **envp);
int		is_key(char c);

//builtings
int		ft_echo(char **args, t_list **var_list);
int		ft_cd(char **args,  t_list **var_list);
int		ft_pwd(char **args,  t_list **var_list);
int		ft_export(char **args,  t_list **var_list);
int		ft_unset(char **args,  t_list **var_list);
int		ft_env(char **args,  t_list **var_list);
int		ft_exit(char **args,  t_list **var_list);

//Execution
t_btree	*ft_start(t_btree *ast, t_list **var_list);
int		ft_start_execution(char **args, t_list **var_list);
int		ft_execution(char **args, t_list **var_list);
t_list	*ft_find_var(t_list **var_list, char *var_name);
int		ft_save_var(t_list **var_list, char *var, int var_id);
void	*ft_make_var(char *var, t_var **variable);
int		ft_clear_vars(t_list **var_list);
int 	ft_chng_var(t_list **var_list, char *var_name, char *new_value, int var_id);
int		ft_change_lvl(t_list **var_list, int id);
int		ft_clear_path_list(char ***path_list);
int		ft_add_status(t_list **var_list, int status);
int		ft_cmd_error(char *cmd);
char	**ft_parse_path(t_list **var_list);
char	*ft_find_path(char **path_list, char *executor_name);
int		ft_join_path(char *args, char *tmp_path, char **path_list, char **executor_path);
int		ft_execute_cmd(char *path, char **args);


// UTILS:
void	sig_handler(int signum);
void	sig_init(void);
t_tlist	*tlistnew(int type);
void	tlistadd_back(t_tlist **head_token, t_tlist *newtoken);
void	tlist_clear(t_tlist *head);
void	tlist_del(t_tlist *head);
void    rl_replace_line(const char *buffer, int val);
void	clear_all(t_tlist **tokens, t_btree *ast);

// DEBUG:
void	print_tokens(t_tlist *tokens);
void 	print_tree(t_btree *ast);

#endif
