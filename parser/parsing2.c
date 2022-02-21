/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:38:28 by acollin           #+#    #+#             */
/*   Updated: 2021/10/09 12:01:13 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



//char	* redirection(char *prompt, int *i)
//{
//	// Только получаем fd от каждого редиректа для дальнейшего dup2 (для
//	// подмены fd)
//	int		fd;
//	int		fd2;
//	int		j;
//	char	*filename;
//
//	j = *i;
//	while (prompt[++(*i)])
//	{
//		if (prompt[*i] != ' ' || prompt[*i] != '|'
//			|| prompt[*i] != '\t' || prompt[*i] != '\n')
//			break ;
//	}
//	filename = ft_strdup(prompt + (*i));
//	if (prompt[j] == '>' && prompt[j + 1] != '>')
//		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//	if (prompt[j] == '>' && prompt[j + 1] == '>')
//		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
//	if (prompt[j] == '<' && prompt[j + 1] != '<')
//		fd2 = open(filename, O_RDONLY, 0644);
//	return (filename);
//}
//
//char	*ft_pipes(char *prompt, int *i)
//{
//	// int *fd1 = malloc(sizeof(int) * NUM_OF_PIPES;
//	// int *fd2 = malloc(sizeof(int) * NUM_OF_PIPES; - это массивы fd,
//	// которые создаются при каждом пайпе
//	char	*tmp;
//
//	tmp = NULL;
//	if (prompt[*i] == '|')
//		tmp = ft_strdup("do the pipes");
//	return (tmp);
//}
//