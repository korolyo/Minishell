/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:38:28 by acollin           #+#    #+#             */
/*   Updated: 2021/10/09 12:01:13 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipes(t_tlist *tokens)
{
	int *fdpipe;

	fdpipe = (int *) ft_calloc(sizeof(int), tokens->pipes);
	if (tokens->pipes != 0)
		pipe(fdpipe);

	switch (kind)
	{
		case start:
			dup2(current_pipe[WRITE], STDOUT_FILENO);
			break;
		case middle:
			dup2(previous_pipe[READ], STDIN_FILENO);
			dup2(current_pipe[WRITE], STDOUT_FILENO);
			break;
		case end:
			dup2(previous_pipe[READ], STDIN_FILENO);
		default:
			break;
	}
}