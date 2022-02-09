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
# define ARG				12
# define	REDIR			22
# define REDIR_APPEND	23
# define REDIR_INPUT		24
# define HERE_DOC		25
# define PIPE			44
# define ENV				55
# define QUOTES			88

// Delimeters:
# define DELIM	" \t"

# define DELETE_MID 7

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
//	char		*token;
	int 		type;
//	char 		*infile;
//	char 		*outfile;
	char		**cmd;
	char 		*args;
//	char 		*envkey;
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
	int		(*f_cmd)(char **args);
}				t_cmd;

// Preparsing
char	*preparse(char *prompt);
char	*preparse_delim(char *prompt, int i);
int		preparse_quotes(char *prompt, int i);
int		preparse_redir(char *prompt, int i);

// Preparsing utils
char	*str_delete_part(char *prompt, int start, int end, int flag_mid);

// LEXER:
void	init_lexer(t_tlist *token);
void	lexer(char *prompt, t_tlist **tokens);
void	lexer_backslash(t_tlist **tokens, char *prompt, int *i);
void	lexer_semicolon(t_tlist **tokens);
void	lexer_quotes(t_tlist **tokens, char *prompt, int *i);
void	lexer_redir(t_tlist **tokens, char *prompt, int *i);
void	lexer_cmd(t_tlist **tokens, char *prompt, int *i);
void	lexer_env(t_tlist **tokens, char *prompt, int *i);
void	lexer_pipe(t_tlist **tokens, int *i);

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
int		ft_echo(char **args);
int		ft_cd(char **args);
int		ft_pwd(char **args);
int		ft_export(char **args);
int		ft_unset(char **args);
int		ft_env(char **args);
int		ft_exit(char **args);

//Execution
t_btree		*start(t_btree *ast);
int start_execution(char **args);
int		ft_execution(char **args);

//Exec Utils - это пока не надо (и вообще не надо, похоже)
//void	*ft_abort(char ***arr, size_t size);
//size_t	get_len(char *str, char c, size_t *i);
//char	**get_str(char ***res, char **str, char c, size_t size);
//size_t	get_arrlen(char const *s, char c);

// UTILS:
t_tlist	*tlistnew(int type);
void	tlistadd_back(t_tlist **head_token, t_tlist *newtoken);
void	tlist_clear(t_tlist **head);
void	tlist_del(t_tlist *head);
void    rl_replace_line(const char *buffer, int val);
void	clear_all(t_tlist **tokens, t_btree *ast);

// DEBUG:
void	print_tokens(t_tlist *tokens);
void 	print_tree(t_btree *ast);

#endif
