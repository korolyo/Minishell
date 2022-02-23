/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:38:28 by acollin           #+#    #+#             */
/*   Updated: 2021/10/09 12:01:13 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tlist	*tlistnew(int type)
{
	t_tlist	*tmp;

	if (!(tmp = (t_tlist *)malloc(sizeof(t_tlist))))
			return (NULL);
	tmp->type = type;
	tmp->cmd = NULL;
	tmp->next = NULL;
	tmp->fdin = -2;
	tmp->fdout = -2;
	tmp->pipes = 0;
	tmp->kind = MIDDLE;
	return (tmp);
}

void	tlistadd_back(t_tlist **head_token, t_tlist *newtoken)
{
	t_tlist	*final;

	if(!head_token && !newtoken)
		return ;
	if (!(*head_token))
	{
		*head_token = newtoken;
		return ;
	}
	final = *head_token;
	while (final->next != NULL)
		final = final->next;
	final->next = newtoken;
}

void	tlist_del(t_tlist *head)
{
	t_tlist	*tmp;

	tmp = head;
	head = head->next;
	if (tmp->cmd)
		free(tmp->cmd);
	free(tmp);
}

void	tlist_clear(t_tlist *head)
{
	if (head == NULL)
		return ;
	tlist_clear(head->next);
	if (head->cmd)
		free(head->cmd);
	head->next = NULL;
	free(head);
}

//t_tlist	*init_lexer(void)
//{
//	t_tlist	*tmp;
//
//	tmp = (t_tlist *)malloc(sizeof(t_tlist));
//	tmp->type = 0;
////	token->infile = NULL;
////	token->outfile = NULL;
//	tmp->cmd = NULL;
//	tmp->next = NULL;
//	tmp->fdin = -1;
//	tmp->fdout = -1;
//	tmp->pipes = 0;
//	return (tmp);
//}