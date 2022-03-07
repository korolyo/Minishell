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

	tmp = (t_tlist *)malloc(sizeof(t_tlist));
	if (!tmp)
		return (NULL);
	tmp->type = type;
	tmp->cmd = NULL;
	tmp->next = NULL;
	tmp->fdin = -2;
	tmp->fdout = -2;
	tmp->pipes = 0;
	tmp->kind = MIDDLE;
	tmp->stop_word = NULL;
	return (tmp);
}

void	tlistadd_back(t_tlist **head_token, t_tlist *newtoken)
{
	t_tlist	*final;

	if (!head_token && !newtoken)
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

void	free_array(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	tlist_clear(t_tlist *head)
{
	if (head == NULL)
		return ;
	tlist_clear(head->next);
	if (head->cmd)
		free_array(head->cmd);
	if (head->stop_word)
		free(head->stop_word);
	head->next = NULL;
	free(head);
}

int	is_key(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}
