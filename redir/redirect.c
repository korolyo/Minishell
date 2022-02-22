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

//void	redirect(t_tlist *ast_node)
//{
//	int		tmpin;
//	int		tmpout;
////	int		ret;
//	t_tlist	*tmp;
//
//	tmpin = dup(0);
//	tmpout = dup(1);
////	tmp = *tokens;
////	if (tmp->infile)
////		fdin = open(tmp->infile, O_RDONLY, 0644);
////	else
////		fdout = dup(tmpin);
////	while (i < numcmd)
////	{
//	dup2(ast_node->fdin, 0);
//	close(ast_node->fdin);
//	if (ast_node->pipes > 0)
//	{
//		int fdpipe[2];
//		pipe(fdpipe);
//		ast_node->fdout = fdpipe[1];
//		ast_node->fdin = fdpipe[0];
//	}
//	dup2(ast_node->fdout, 1);
//	close(ast_node->fdout);
////		i++;
////		ret = fork();
////		if (ret == 0)
////			exit(1);
////	}
//	dup2(tmpin, 0);
//	dup2(tmpout, 1);
//	close(tmpin);
//	close(tmpout);
//}