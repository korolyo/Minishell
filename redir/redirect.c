/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:38:28 by acollin           #+#    #+#             */
/*   Updated: 2021/10/09 12:01:13 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect(t_tlist *tokens)
{
	int		tmpin;
	int		tmpout;
	int		ret;
	t_tlist	*tmp;
//
	tmpin = dup(0);
	tmpout = dup(1);
//	tmp = *tokens;
	if (tmp->infile)
//		fdin = open(tmp->infile, O_RDONLY, 0644);
//	else
//		fdout = dup(tmpin);
//	while (i < numcmd)
//	{
//		dup2(fdin, 0);
//		close(fdin);
//		else
//		{
//			int fdpipe[2];
//			pipe(fdpipe);
//			fdout = fdpipe[1];
//			fdin = fdpipe[0];
//		}
//
//		dup2(fdout, 1);
//		close(fdout);
//		i++;
//		ret = fork();
//		if (ret == 0)
//			exit(1);
//	}
//		dup2(tmpin, 0);
//		dup2(tmpout, 1);
//		close(tmpin);
//		close(tmpout);
//}