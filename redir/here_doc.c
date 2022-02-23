/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:38:28 by acollin           #+#    #+#             */
/*   Updated: 2021/10/09 12:01:13 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *stop_word, t_tlist *tokens)
{
	char *here_doc;
	int fd_in_hd;

	if (!(fd_in_hd = open(".tmp_hd", O_WRONLY | O_CREAT | O_APPEND, 0644)))
		perror("Cant create tmp file");
	while (не нашли стоп
	слово)
	{
		while (1)
		{
			here_doc = prompt("> ");

		};
	}
	tokens->fdin = fd_in_hd;
	.....
}