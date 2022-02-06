/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:38:28 by acollin           #+#    #+#             */
/*   Updated: 2021/10/09 12:01:13 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_key(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

int	build_ast(t_tlist **tokens, t_btree *ast)
{
	t_tlist	*lnode;
	t_tlist	*left_tmp;
	t_tlist	*right_tmp;
	t_btree	*tnode;

	lnode = *tokens;
	left_tmp = *tokens;
	while (lnode)
	{
		if (lnode->type == PIPE)
		{
			ast->type = PIPE;
			ast->left = add_node(ast, left_tmp);
			ast->right = add_node(ast, lnode->next);
			tlist_del(lnode);
		}
		if (lnode->type == REDIR || lnode->type == REDIR_INPUT ||
			lnode->type == REDIR_APPEND)
		{
			ast->type = REDIR;
			ast->left =
		}
		if (lnode->type == CMD)
		{
			ast->type = CMD;
			tlist_del(lnode);
		}
		lnode = lnode->next;
	}
}

int	parse_line(t_tlist *tokens, t_btree *ast)
{
	t_tlist	*tmp_lst;

	tmp_lst = tokens;
	if (!(build_ast(&tokens, &ast)))
		return (0);
	return (1);
}
