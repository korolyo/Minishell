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
//# include <readline.h>
//# include <history.h>
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

typedef struct s_data		t_data;
typedef struct s_textbuf	t_textbuf;

struct		s_data
{
	char *env_key;
};

struct	s_textbuf
{
	char		**token;
	t_textbuf	*next;
};

void	preparse(char *prompt, t_textbuf *textbuf);
void	parse_line(char *str, char **envp);
char	*ft_quotes(char *prompt, int *i);
char	*ft_dollar(char *prompt, int *i, t_data *data, char **envp);
int		is_key(char c);
void	clear_all(char *prompt);

#endif
