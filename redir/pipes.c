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

int find_cmd_num(t_tlist *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}


void	pipes(t_tlist *tokens)
{
	int	*fdpipe;
	int	count_cmd;
	int	i;
	int	err;

	i = 0;
	count_cmd = find_cmd_num(tokens);
	fdpipe = (int *) ft_calloc(sizeof(int), tokens->pipes);
	while (count_cmd != 0)
	{
		if ((err = pipe(fdpipe + 2 * i)) == -1)
		{
			free(pipe);
			perror("Bad piping");
			exit(err);
		}
		count_cmd--;
	}
}

void	cmd_kind(t_tlist *tokens)
{
	tokens->kind = FIRST;
	while (tokens->next)
		tokens = tokens->next;
	tokens->kind = LAST;
}

void	pipe_switch(t_tlist *tokens, int *i, int *fdpipe)
{
	if (tokens->kind == FIRST)
	{
		dup2(fdpipe[2 * (*i) + 1], STDOUT_FILENO);
		break;
	}
	else if (tokens->kind == MIDDLE)
	{
		dup2(fdpipe[2 * (*i) - 1], STDIN_FILENO);
		dup2(fdpipe[2 * (*i) + 1], STDOUT_FILENO);
		break;
	}
	else if (tokens->kind == LAST)
	{
		dup2(fdpipe[2 * (*i) - 1], STDIN_FILENO);
		break;
	}
}