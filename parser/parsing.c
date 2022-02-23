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

//t_tlist	*right_lst(t_tlist *tokens)
//{
//	t_tlist	*curr;
//	t_tlist	*newnode;
//
//	curr = tokens;
//	newnode = NULL;
//	if (curr)
//	{
//		newnode = tlistnew(0);
//		newnode->cmd = curr->cmd;
//		newnode->type = curr->type;
//		newnode->next = right_lst(curr->next);
//		return (newnode);
//	}
//	return (NULL);
//}
//
//t_tlist	*left_lst(t_tlist *tokens, int i)
//{
//	t_tlist	*curr;
//	t_tlist	*newnode;
//
//	curr = tokens;
//	newnode = NULL;
//	i--;
//	if (i > 0)
//	{
//		if (curr == NULL)
//			return (NULL);
//		else
//		{
//			newnode = tlistnew(0);
//			newnode->cmd = curr->cmd;
//			newnode->type = curr->type;
//			newnode->next = left_lst(curr->next, i);
//			return (newnode);
//		}
//	}
//	return (NULL);
//}
//
//int find_index(t_tlist *tokens, int type)
//{
//	int	i;
//
//	i = 0;
//	while (tokens)
//	{
//		if (tokens->type == type)
//			return (i);
//		i++;
//		tokens = tokens->next;
//	}
//	return (-1);
//}

//t_btree	*build_ast(t_tlist *tokens)
//{
//	t_tlist	*lnode;
//	t_tlist	*left_tmp;
//	t_tlist	*right_tmp;
//	t_btree	*tnode;
//	int 	i;
//
//	i = 0;
//	if (!tokens)
//		return (NULL);
//	lnode = tokens;
//	tnode = btreenew(0);
////	if ((i = find_index(tokens, PIPE)) != -1)
////	{
////		i++;
////		left_tmp = left_lst(tokens, i);
////		while (--i > 0)
////			tokens = tokens->next;
////		tnode->type = PIPE;
////		tnode->value = tokens->cmd;
////		right_tmp = right_lst(tokens->next);
////		tnode->left = build_ast(left_tmp);
////		tnode->right = build_ast(right_tmp);
////	}
////	else if (((i = find_index(tokens, REDIR)) != -1)
////		|| ((i = find_index(tokens, REDIR_INPUT)) != -1)
////		|| ((i = find_index(tokens, REDIR_APPEND)) != -1))
////	{
////		i++;
////		left_tmp = left_lst(tokens, i);
////		while (--i > 0)
////			tokens = tokens->next;
////		tnode->type = REDIR;
////		tnode->value = tokens->cmd;
////		right_tmp = right_lst(tokens->next);
////		tnode->left = build_ast(left_tmp);
////		tnode->right = build_ast(right_tmp);
////	}
//	else if (lnode->type == CMD)
//	{
//		tnode->value = lnode->cmd;
//		tnode->type = CMD;
//		tnode->pipes = lnode->pipes;
//		tnode->fdin = lnode->fdin;
//		tnode->fdout = lnode->fdout;
//		tnode->left = build_ast(lnode->next);
//	}
//	return (tnode);
//}
//
//t_btree *parse_line(t_tlist *tokens)
//{
//	t_btree *tmp;
//
////	tmp = build_ast(tokens);
////	printf("ast:\n");
////	print_tree(tmp);
//	if (!(tmp = build_ast(tokens)))
//		return (NULL);
//	return (tmp);
//}
//
//void print_tree(t_btree *ast)
//{
//	int	i;
//
//	i = -1;
//	if (ast)
//	{
//		print_tree(ast->left);
//		while (ast->value[++i])
//			printf("[%s]\n", ast->value[i]);
//		print_tree(ast->right);
//	}
//}