/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 22:00:12 by acollin           #+#    #+#             */
/*   Updated: 2021/08/04 22:00:14 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*tmp;

	tmp = (t_list *) ft_calloc(sizeof (t_list), 1);
	if (NULL == tmp)
		return (NULL);
	tmp->content = content;
	tmp->next = NULL;
	return ((t_list *)tmp);
}
