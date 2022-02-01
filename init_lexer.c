/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:38:28 by acollin           #+#    #+#             */
/*   Updated: 2021/10/09 12:01:13 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tlist	*tlistnew(char *cmd, int type, char *args)
{
	t_tlist	*tmp;

	if (!(tmp = (t_tlist *)malloc(sizeof(t_tlist))))
			return (NULL);
	tmp->type = type;
	tmp->cmd = ft_strdup(cmd);
	tmp->args = NULL;
	tmp->next = NULL;
	return (tmp);
}

void tlistadd_back(t_tlist **head_token, t_tlist *newtoken)
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

int init_lexer(t_tlist *token, char *prompt)
{
	t_tlist	*token_head;
	t_tlist	*token;

	if (!)
	return (1);
}