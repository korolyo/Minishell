/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:38:28 by acollin           #+#    #+#             */
/*   Updated: 2021/10/09 12:01:13 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_btree	*btreenew(int type)
{
	t_btree	*node;

	node = (t_btree *)malloc(sizeof(t_btree));
	if (!node)
		return (NULL);
	node->value = (char **)malloc(sizeof(char *) * 2);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->fdon = -1;
	node->fdout = -1;
	node->pipes = 0;
	return (node);
}

void	clear_ast(t_btree *ast)
{
	if (ast == NULL)
		return ;
	clear_ast(ast->left);
	clear_ast(ast->right);
	free(ast);
}
