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

t_tlist	*right_lst(t_tlist *tokens)
{
	t_tlist	*curr;
	t_tlist	*newnode;

	curr = tokens;
	newnode = NULL;
	if (curr)
	{
		newnode = tlistnew(NULL, 0, NULL);
		newnode->cmd = ft_strdup(curr->cmd);
		newnode->type = curr->type;
		newnode->args = ft_strdup(curr->args);
		newnode->next = right_lst(curr->next);
//		printf("right side: ");
//		print_tokens(newnode);
		return (newnode);
	}
	return (NULL);
}

t_tlist	*left_lst(t_tlist *tokens, int i)
{
	t_tlist	*curr;
	t_tlist	*newnode;

	curr = tokens;
	newnode = NULL;
	i--;
	if (i > 0)
	{
		if (curr == NULL)
			return (NULL);
		else
		{
			newnode = tlistnew(NULL, 0, NULL);
			newnode->cmd = ft_strdup(curr->cmd);
			newnode->type = curr->type;
			newnode->args = ft_strdup(curr->args);
//			printf(" i = %d, newnode->cmd = |%s|\n", i, newnode->cmd);
			newnode->next = left_lst(curr->next, i);
//			printf("left side: ");
//			print_tokens(newnode);
			return (newnode);
		}
	}
	return (NULL);
}

int find_index(t_tlist *tokens, int type)
{
	int	i;

	i = 0;
	while (tokens)
	{
		if (tokens->type == type)
			return (i);
		i++;
		tokens = tokens->next;
	}
	return (-1);
}

t_btree	*build_ast(t_tlist *tokens)
{
	t_tlist	*lnode;
	t_tlist	*left_tmp;
	t_tlist	*right_tmp;
	t_btree	*tnode;
	int 	i;

	i = 0;
//	printf("inside of Build_ast(PIPE)\n");
	if (!tokens)
		return (NULL);
	lnode = tokens;
	tnode = btreenew(0);
	if ((i = find_index(tokens, PIPE)) != -1)
	{
//		printf("inside of Build_ast(PIPE)\n");
		i++;
		left_tmp = left_lst(tokens, i);
//			print_tokens(left_tmp);
		while (--i > 0)
			tokens = tokens->next;
		tnode->type = PIPE;
		tnode->value = ft_strdup(tokens->cmd);
		right_tmp = right_lst(tokens->next);
//			printf("inside of Build_ast(PIPE)\n");
		tnode->left = build_ast(left_tmp);
		tnode->right = build_ast(right_tmp);
//		printf("tree in pipe\n");
//		print_tree(tnode);
	}
	else if (((i = find_index(tokens, REDIR)) != -1)
		|| ((i = find_index(tokens, REDIR_INPUT)) != -1)
		|| ((i = find_index(tokens, REDIR_APPEND)) != -1))
	{
		i++;
//		printf("inside of Build_ast(REDIR)\n");
//		printf("i = %d\n", i);
		left_tmp = left_lst(tokens, i);
		while (--i > 0)
			tokens = tokens->next;
		tnode->type = REDIR;
		tnode->value = ft_strdup(tokens->cmd);
		right_tmp = right_lst(tokens->next);
//		printf("check redir\n");
		tnode->left = build_ast(left_tmp);
		tnode->right = build_ast(right_tmp);
//		printf("tree in redir\n");
//		print_tree(tnode);
	}
	else if (lnode->type == CMD)
	{
//		printf("inside of Build_ast(CMD)\n");
		tnode->value = ft_strdup(lnode->cmd);
		tnode->type = CMD;
		tnode->left = build_ast(lnode->next);
//		printf("check\n");
	}
//	printf("check\n");
//	printf("tokens->type = %d\n", tokens->type);
	return (tnode);
}

int	parse_line(t_tlist *tokens, t_btree *ast)
{
	ast = build_ast(tokens);
//	printf("ast:\n");
//	print_tree(ast);
//	if (!(ast = build_ast(tokens)))
//		return (0);
	return (1);
}

void print_tree(t_btree *ast)
{
	if (ast)
	{
		print_tree(ast->left);
		printf("[%s]\n", ast->value);
		print_tree(ast->right);
	}
}