/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:41:28 by acollin           #+#    #+#             */
/*   Updated: 2021/10/06 20:42:12 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PREPARSER_H
# define PREPARSER_H

# include "libft.h"

# define DELIM	" \t"

# define DELETE_MID	7

char	*preparse(char *prompt);
int		unmatched_quotes(char *prompt, int i);
void	preparse_quotes(char const *prompt, int *i);
char	*preparse_delim(char *prompt, int i);
int		preparse_redir(char *prompt, int i);
int		preparse_pipe(char *prompt, int i);
char	*prep_clear(char *str, char *tmp, char *prompt);
char	*delim_str(char *prompt, int *i, char *tmp);

// Utils
char	*str_delete_part(char *input, int start, int end, int flag_mid);

#endif
