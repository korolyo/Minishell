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

static void	make_tmp_file_input(t_tlist *tokens)
{
	tokens->fdin = open(".tmp_file", O_RDONLY, 0644);
	unlink(".tmp_file");
	dup2(tokens->fdin, 0);
	close(tokens->fdin);
}

void	heredoc(t_tlist *tokens)
{
	int		fd;
	char	*line;

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
	close(fd);
}

void	here_doc_input(t_tlist *tokens)
{
	int	save_fd_out;

	save_fd_out = dup(1);
	dup2(tokens->fdout, STDOUT_FILENO);
	signal(SIGINT, SIG_IGN);
	heredoc(tokens);
	make_tmp_file_input(tokens);
}
