/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:38:28 by acollin           #+#    #+#             */
/*   Updated: 2021/10/09 12:01:13 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_all(char *prompt, t_tlist **tokens, t_btree *ast)
{
	free(prompt);
	tlist_clear(tokens);
	clear_ast(ast);
	ast = NULL;
}

void	print_tokens(t_tlist *tokens)
{
	t_tlist	*current_node;
	int		i;

	i = 0;
	current_node = tokens;
	while (current_node != NULL)
	{
		printf("[%s] ->", current_node->cmd);
		current_node = current_node->next;
		i++;
	}
	printf("\nnum of nodes = %d\n", i);
}

int	main(void)
{
	char	*prompt;
	t_tlist	*tokens;
	t_btree	*ast;

	tokens = NULL;
	ast = NULL;
	prompt = readline("minishell >");
	if (prompt)
	{
		printf("prompt: |%s|\n", prompt);
		add_history(prompt);
		prompt = preparse(prompt);
//		printf("preparse: |%s|\n", prompt);
		lexer(prompt, &tokens);
//		printf("tokens :");
//		print_tokens(tokens);
//		printf("main check \n");
		if (!(parse_line(tokens, ast)))
			printf("problem with AST");
//		printf("check\n");
//	printf("preparse: |%s|\n", prompt);
		clear_all(prompt, &tokens, ast);
	}
	exit(EXIT_SUCCESS);
}
