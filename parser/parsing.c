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

t_tlist	*left_right_lst()
{
	t_tlist	*newnode;

	newnode = tlistnew()
	return (newnode);
}

t_btree	*build_ast(t_tlist **tokens)
{
	t_tlist	*lnode;
	t_tlist	*left_tmp;
	t_tlist	*right_tmp;
	t_tlist	*tmplist;
	t_tlist	*tmp;
	t_btree	*tnode;
	int 	i;

	i = 0;
	lnode = tokens;
	tmp = tokens;
	tnode = btreenew(0);
	while (lnode)
	{
		if (lnode->type == PIPE)
		{
			while (i > 0)
			{
				left_tmp = tlistnew(tmp->cmd, tmp->type, tmp->args);
				tlistadd_back(&left_tmp, left_tmp);
				tmp = tmp->next;
				printf("i = %d\n", i);
				i--;
			}
			tmp = lnode->next;
			while (tmp)
			{
				right_tmp = tlistnew(tmp->cmd, tmp->type, tmp->args);
				tlistadd_back(&right_tmp, tmp);
				tmp = tmp->next;
			}
			tnode->type = PIPE;
//			tlist_del(lnode);
			tnode->left = build_ast(left_tmp);
			tnode->right = build_ast(right_tmp);
		}
		printf("inside of Build_ast(PIPE)\n");
		i++;
		lnode = lnode->next;
	}
	i = 0;
	lnode = tokens;
//	tmp = *tokens;
	while (lnode)
	{
		if (lnode->type == REDIR || lnode->type == REDIR_INPUT
			|| lnode->type == REDIR_APPEND)
		{
			while (i > 0)
			{
				left_tmp = tlistnew(tmp->cmd, tmp->type, tmp->args);
				tlistadd_back(&left_tmp, tmp);
				tmp = tmp->next;
				i--;
				printf("i = %d inside of Build_ast(REDIR)\n", i);
				print_tokens(left_tmp);
			}
			tmp = lnode->next;
			while (tmp)
			{
				right_tmp = tlistnew(tmp->cmd, tmp->type, tmp->args);
				tlistadd_back(&right_tmp, tmp);
				tmp = tmp->next;
				print_tokens(right_tmp);
			}
			tnode->type = REDIR;
//			tlist_del(lnode);
			tnode->left = build_ast(left_tmp);
			tnode->right = build_ast(right_tmp);
		}
		printf("inside of Build_ast(REDIR)\n");
		i++;
		lnode = lnode->next;
	}
	if (lnode->type == CMD)
	{
		printf("inside of Build_ast(CMD)\n");
		tnode->type = CMD;
		return (NULL);
	}
	return (tnode);
}

int	parse_line(t_tlist **tokens, t_btree *ast)
{
	if (!(ast = build_ast(tokens)))
		return (0);
	return (1);
}
