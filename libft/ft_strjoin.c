/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 22:04:25 by acollin           #+#    #+#             */
/*   Updated: 2021/08/04 22:04:27 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned char	*new;
	unsigned char	*ret;
	size_t			plen;
	size_t			slen;

	plen = ft_strlen(s1);
	slen = ft_strlen(s2);
	new = (unsigned char *)ft_calloc((plen + slen + 1), sizeof(char));
	if ((void *)0 == new)
		return ((void *)0);
	ret = new;
	while (plen-- > 0)
		*new++ = *s1++;
	while (slen-- > 0)
		*new++ = *s2++;
	return ((char *) ret);
}
