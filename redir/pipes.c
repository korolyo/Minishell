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

int	find_cmd_num(t_tlist *tokens)
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

int	*pipes(t_misc *misc)
{
	int	*fdpipe;
	int	i;

	i = 0;
	fdpipe = (int *) ft_calloc(sizeof(int), 2 * misc->num_of_pipes);
	while (i < (misc->cmd_count - 1))
	{
		if (pipe(fdpipe + 2 * i) == -1)
			perror("Bad piping");
		i++;
	}
	return (fdpipe);
}

void	cmd_kind(t_tlist *tokens)
{
	tokens->kind = FIRST;
	while (tokens->next)
		tokens = tokens->next;
	tokens->kind = LAST;
}

void	pipe_switch(t_tlist *tokens, t_misc *misc)
{
//	printf("tokens->kind = %d\n", tokens->kind);
//	if (misc->cmd_count == 2)
//	{
//		if (tokens->kind == FIRST && tokens->next != NULL)
//			dup2(misc->fdpipe[1], 1);
//		else if (tokens->kind == LAST)
//			dup2(misc->fdpipe[0], 0);
//	}
//	else
//	{
		if (tokens->kind == FIRST)
			dup2(misc->fdpipe[2 * (misc->i) + 1], STDOUT_FILENO);
		else if (tokens->kind == MIDDLE)
		{
			dup2(misc->fdpipe[2 * (misc->i) - 2], STDIN_FILENO);
			dup2(misc->fdpipe[2 * (misc->i) + 1], STDOUT_FILENO);
		}
		else if (tokens->kind == LAST)
			dup2(misc->fdpipe[2 * (misc->i) - 2], STDIN_FILENO);
//	}
}

void	close_pipes(int *fdpipe, int node_id)
{
	int	i;
	int	n;

	i = 0;
	n = 2 * (node_id - 1);
	while (i < n)
		close(fdpipe[i++]);
}

void	init_misc(t_misc *misc, t_tlist *tokens)
{
	misc->cmd_count = find_cmd_num(tokens);
	misc->i = 0;
	misc->num_of_pipes = tokens->pipes;
	misc->fdpipe = NULL;
}
