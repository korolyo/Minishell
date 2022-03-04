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

void	heredoc(t_tlist *tokens)
{
	int		fd;
	char	*line;

	signal(SIGINT, SIG_IGN);
	signal(SIGINT, interrupt_here_document);
	fd = open(".tmp_file", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, tokens->stop_word, ft_strlen(line)) == 0)
		{
			close(fd);
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
	}
	tokens->fdin = fd;
	close(fd);
	exit(0);
}
