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

//void	clear_all(t_tlist **tokens, char *prompt)
//{
//	unlink(".tmp_file");
//	if (prompt)
//		free(prompt);
//	if (*tokens)
//		*tokens = NULL;
//}

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

t_list	*save_var(char **envp)
{
	t_list		*var_list;

	var_list = NULL;
	while (*envp != NULL)
	{
		ft_save_var(&var_list, *envp, 1);
		envp++;
	}
	ft_save_var(&var_list, "?=0", 0);
	return (var_list);
}

void	check_eof(char *line)
{
	if (line)
		return ;
	printf("exit\n");
	exit(g_exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	char		*prompt;
	char		*input;
	t_tlist		*tokens;
	t_list		*var_list;

	(void)argc;
	(void)argv;
	var_list = save_var(envp);
	ft_change_lvl(&var_list, 1);

	printf("chaeck1\n");
	while (1)
	{
		tokens = NULL;
		prompt = create_prompt();
		printf("chaeck2\n");
		sig_init();
		input = readline(prompt);
		if (input)
			add_history(input);
		input = preparse(input);
		if (input)
		{
			lexer(input, &tokens, &var_list);
			if (!(ft_start(tokens, &var_list)))
				printf("problem with executor");
			printf("finish1\n");
			tlist_clear(tokens);
		}
		printf("finish1\n");
		free(prompt);
	}
	ft_clear_vars(&var_list);
	exit(EXIT_SUCCESS);
}
