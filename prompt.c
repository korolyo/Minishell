/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:38:28 by acollin           #+#    #+#             */
/*   Updated: 2021/10/09 12:01:13 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*concatenate_prompt(char *name, char *end)
{
	char	*prompt;

	prompt = variadic_strjoin(
			5,
			ESC_BOLD_PURPLE,
			name,
			ESC_BOLD_RED,
			end,
			ESC_RESET_COLOR);
	free(name);
	free(end);
	return (prompt);
}

char	*create_name(void)
{
	return (ft_strdup("Minichill \U0001f3c4:"));
}

char	*create_prompt(void)
{
	char	*name;
	char	*end;

	name = create_name();
	end = ft_strdup("$ ");
	return (concatenate_prompt(name, end));
}
