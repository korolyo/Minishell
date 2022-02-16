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
////	printf("check\n");
	if (*tokens)
	{
		tlist_clear(*tokens);
		*tokens = NULL;
	}
	if (ast)
		clear_ast(ast);
////	ast = NULL;
}

void	print_tokens(t_tlist *tokens)
{
	t_tlist	*current_node;
	int		i;
	int		j;

	i = 0;
	current_node = tokens;
	if (!tokens)
	{
		printf("no tokens");
		return ;
	}
	while (current_node != NULL)
	{
		printf("[");
		j = -1;
		while (current_node->cmd[++j])
			printf("%s ", current_node->cmd[j]);
		printf("]->");
		current_node = current_node->next;
		i++;
	}
	printf("\nnum of nodes = %d\n", i);
}

int	main(void)
{
	char		*prompt;
	t_tlist		*tokens;
	t_btree		*ast;
	int			*fd;
	t_list		*var_list;
	extern char	**environ;

	tokens = NULL;
	ast = NULL;
	fd = NULL;
	var_list = NULL;
	while (*environ != NULL)
	{
		ft_save_var(&var_list, *environ, 1);
		environ++;
	}
	ft_save_var(&var_list, "?=0", 0); //  здесь делаем переменную для хранения статуса
	//rl_catch_signals = 0;
	ft_change_lvl(&var_list, 1);
	while (1)
	{
//		tokens = NULL;
//		ast = NULL;
//		fd = NULL;
//		if (!var_list)
//			var_list = NULL;
		//sig_init();
		prompt = readline("minishell > ");
//		printf("prompt: |%s|\n", prompt);
		if (prompt)
			add_history(prompt);
		if (!(prompt = preparse(prompt)))
			exit(EXIT_SUCCESS);
//		printf("preparse: |%s|\n", prompt);
		lexer(prompt, &tokens, &var_list);
//		printf("tokens :");
//		print_tokens(tokens);
		if (!(ast = parse_line(tokens)))
			printf("problem with AST");
//		printf("check1\n");
		if (!(ft_start(ast, &var_list)))
			printf("problem with executor");      //EXECUTION
//		printf("main check \n");
		clear_all(&tokens, ast);
	}
	exit(EXIT_SUCCESS);
}
