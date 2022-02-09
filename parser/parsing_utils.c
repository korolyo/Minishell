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
	return (node);
}

//void	free_node_tree(t_btree *node)
//{
//	t_btree	*child;
//	t_btree	*next;
//
//	if (!node)
//		return ;
//	child = node->first_child;
//	while (child)
//	{
//		next = child->next_sibling;
//		free_node_tree(child);
//		child = next;
//	}
//	if (node->type == VAL_STR)
//		if (node->val.str)
//			free(node->val.str);
//	free(node);
//}

void	clear_ast(t_btree *ast)
{
	if (ast == NULL)
		return ;
	free(ast->value);
	clear_ast(ast->left);
	clear_ast(ast->right);
	free(ast);
}