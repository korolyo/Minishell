/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 21:58:43 by acollin           #+#    #+#             */
/*   Updated: 2021/08/04 21:58:45 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*final;

	if (!lst && !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	final = *lst;
	while (final->next != NULL)
		final = final->next;
	final->next = new;
}
