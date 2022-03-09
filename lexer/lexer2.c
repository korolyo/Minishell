/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:38:28 by acollin           #+#    #+#             */
/*   Updated: 2021/10/09 12:01:13 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_value(t_list **var_list, char *tmp2)
{
	char	*ret;
	t_list	*tmp4;
	t_var	*tmp5;

	ret = NULL;
	if (tmp2)
	{
		tmp4 = ft_find_var(var_list, tmp2);
		if (!tmp4 && tmp2[0] != '$')
			ret = NULL;
		if (tmp2[0] == '$')
			ret = ft_strdup("$");
		else if (tmp4)
		{
			tmp5 = (t_var *) tmp4->content;
			ret = ft_strdup(tmp5->value);
		}
	}
	free(tmp2);
	return (ret);
}

char	*join_dollar(char *tmp, char *tmp2, char *tmp3)
{
	char	*ret;
	char	*ret1;

	ret = ft_strjoin(tmp, tmp2);
	if (tmp2)
		free(tmp2);
	if (tmp)
		free(tmp);
	ret1 = ft_strjoin(ret, tmp3);
	if (ret)
		free(ret);
	if (tmp3)
		free(tmp3);
	return (ret1);
}
