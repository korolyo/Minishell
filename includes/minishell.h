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
# include "lexer.h"
# include "preparser.h"
# include "executor.h"
# include "signal.h"
# include "prompt.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <fcntl.h>

// UTILS:
void	clear_all(t_tlist **tokens, char *prompt);

//PIPING
int		*pipes(t_misc *misc);
void	cmd_kind(t_tlist *tokens);
void	pipe_switch(t_tlist *tokens, t_misc *misc);
int		find_cmd_num(t_tlist *tokens);
void	close_pipes(int *fdpipe, int node_id);
void	heredoc(t_tlist *tokens);
void	here_doc_input(t_tlist *tokens);

// DEBUG:
void	print_tokens(t_tlist *tokens);

#endif
