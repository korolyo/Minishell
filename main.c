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

void	clear_all(t_tlist **tokens)
{
	unlink(".tmp_file");
	if (*tokens)
	{
		tlist_clear(*tokens);
		*tokens = NULL;
	}
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

t_list	*save_var(void)
{
	extern char	**environ;
	t_list		*var_list;

	var_list = NULL;
	while (*environ != NULL)
	{
		ft_save_var(&var_list, *environ, 1);
		environ++;
	}
	ft_save_var(&var_list, "?=0", 0);
	return (var_list);
}

int	main(void)
{
	char		*prompt;
	t_tlist		*tokens;
	t_list		*var_list;

	tokens = NULL;
	var_list = save_var();
	rl_catch_signals = 0;
	ft_change_lvl(&var_list, 1);
	while (1)
	{
		sig_init();
		prompt = readline("minishell > ");
		if (prompt)
			add_history(prompt);
		prompt = preparse(prompt);
		if (!prompt)
			exit(EXIT_SUCCESS);
		lexer(prompt, &tokens, &var_list);
		if (!(ft_start(tokens, &var_list)))
			printf("problem with executor");
		clear_all(&tokens);
	}
	ft_clear_vars(&var_list);
	exit(EXIT_SUCCESS);
}

//		printf("tokens :");
//		print_tokens(tokens);
