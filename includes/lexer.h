/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:41:28 by acollin           #+#    #+#             */
/*   Updated: 2021/10/06 20:42:12 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

// KIND OF TOKEN
# define FIRST			0
# define MIDDLE			1
# define LAST			2

// TOKEN types
# define CMD				11
# define REDIR			22
# define REDIR_APPEND	23
# define REDIR_INPUT		24
# define HERE_DOC		25
# define PIPE			44

// Linked list of tokens:
typedef struct s_tlist	t_tlist;

struct		s_tlist
{
	int		type;
	char	**cmd;
	int		pipes;
	int		fdin;
	int		fdout;
	int		kind;
	char	*stop_word;
	t_tlist	*next;
};

char	*dollar_string(char *tmp, t_list **var_list);
char	**ft_quotes_split(char const *str, char c);
void	*ft_quotes_abort(char ***arr, int size);
int		get_quotes_len(char *str, char c, int *i);
int		get_quotes_arrlen(char const *s, char c);
char	**get_quotes_str(char ***res, char **str, char c, int size);
void	lexer(char *prompt, t_tlist **tokens, t_list **var_list);
char	*lexer_quotes(char *prompt, int *i, t_list **var_list);
char	*lexer_dollar(char *prompt, int *i, t_list **var_list);
char	*lexer_redir(t_tlist **tokens, char *prompt, int i);
void	lexer_cmd(t_tlist **tokens, char *prompt);
char	*lexer_pipe(t_tlist **tokens, int *i, char *tmp);
int		find_type(char *prompt, int j, int *i);
char	*join_dollar(char *tmp, char *tmp2, char *tmp3);
char	*find_value(t_list **var_list, char *tmp2);

// UTILS:
t_tlist	*tlistnew(int type);
void	tlistadd_back(t_tlist **head_token, t_tlist *newtoken);
void	tlist_clear(t_tlist *head);
void	check_eof(char *line);
int		is_key(char c);
t_list	*save_var(void);

#endif
