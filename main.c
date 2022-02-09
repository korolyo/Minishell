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

void	clear_all(t_tlist **tokens, t_btree *ast)
{
	printf("check\n");
	if (tokens)
		tlist_clear(tokens);
	if (ast)
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
	int		*fd;
	//EXECUTIOIN
//	char *args[] = {"mkdir", "my_dir", NULL};
//	char **envp = NULL;

	tokens = NULL;
	ast = NULL;
	fd = NULL;
//	if (pipe(fd) == -1)
//		return (-1);
	while (1)
	{
		prompt = readline("minishell >");
		printf("prompt: |%s|\n", prompt);
		if (prompt)
			add_history(prompt);
		prompt = preparse(prompt);
//		printf("preparse: |%s|\n", prompt);
		lexer(prompt, &tokens);
//		printf("tokens :");
//		print_tokens(tokens);
		if (!(parse_line(tokens, ast)))
			printf("problem with AST");
//		free(prompt);

		if (!(start_executing(ast, args, envp)))
			printf("problem with executor");//EXECUTION
//		printf("check\n");
//	printf("preparse: |%s|\n", prompt);
		printf("main check \n");
		clear_all(&tokens, ast);
	}
	exit(EXIT_SUCCESS);
}
