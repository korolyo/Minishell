/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 22:05:30 by acollin           #+#    #+#             */
/*   Updated: 2021/08/04 22:05:33 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned const char	*str1;
	unsigned const char	*str2;
	int					status;

	str1 = (unsigned const char *) s1;
	str2 = (unsigned const char *) s2;
	status = 0;
	if (s1 == s2 || n == 0)
		return (status);
	while (n)
	{
		if (*str1 != *str2++)
			return (*str1 - *(--str2));
		if (*str1++ == 0)
			break ;
		n--;
	}
	return (status);
}
