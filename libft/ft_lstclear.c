/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 21:59:08 by acollin           #+#    #+#             */
/*   Updated: 2021/08/04 21:59:11 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*nextnode;

	tmp = *lst;
	while (tmp != NULL)
	{
		nextnode = tmp->next;
		del(tmp->content);
		free(tmp);
		tmp = nextnode;
	}
	*lst = NULL;
}
