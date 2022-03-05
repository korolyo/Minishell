/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:17:37 by acollin           #+#    #+#             */
/*   Updated: 2022/02/27 17:17:39 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_restore_fd(int tmp_in, int tmp_out)
{
	dup2(tmp_in, STDIN_FILENO);
	close(tmp_in);
	dup2(tmp_out, STDOUT_FILENO);
	close(tmp_out);
}

int	ft_redirection(t_tlist *tokens, int *tmp_in, int *tmp_out)
{
	*tmp_in = dup(STDIN_FILENO);
	*tmp_out = dup(STDOUT_FILENO);
	if (tokens->fdin == -2)
		tokens->fdin = dup(*tmp_in);
	dup2(tokens->fdin, STDIN_FILENO);
	close(tokens->fdin);
	if (tokens->fdout == -2)
		tokens->fdout = dup(*tmp_out);
	dup2(tokens->fdout, STDOUT_FILENO);
	close(tokens->fdout);
	return (1);
}
