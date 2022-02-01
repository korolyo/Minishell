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

# define CMD		11
# define	REDIR	22

# define DELETE_MID 7

typedef struct s_data	t_data;
typedef struct s_tlist	t_tlist;

struct		s_data
{
	char *env_key;
};

struct			s_tlist
{
	char		*token;
	int 		type;
	char 		*infile;
	char 		*outfile;
	char		*cmd;
	int 		type;
	char 		*args;
	t_tlist		*next;
};

//Preparsing
char	*preparse(char *prompt);
char	*preparse_delim(char *prompt, int i);
int		preparse_quotes(char *prompt, int i);
int		preparse_redir(char *prompt, int i);
// Preparsing utils
char *str_delete_part(char *prompt, int start, int end, int flag_mid);

void	tokenization(t_tlist *tokens, char *prompt);
char	*parse_line(char *prompt, char **envp);
char	*ft_backslash(char *prompt, int *i);
char	*ft_quotes(char *prompt, int *i);
char	*ft_doublequotes(char *prompt, int *i);
char	*ft_dollar(char *prompt, int *i, t_data *data, char **envp);
int		is_key(char c);
void	clear_all(char *prompt);
void    rl_replace_line(const char *buffer, int val);

#endif
