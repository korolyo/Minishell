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

void	clear_all(char *input, t_tlist *tokens, char *prompt)
{
	unlink(".tmp_file");
	if (input)
		free(input);
	if (tokens)
		tlist_clear(tokens);
	if (prompt)
		free(prompt);
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
}

t_list	*save_var(void)
{
	t_list		*var_list;
	extern char	**environ;

	var_list = NULL;
	while (*environ != NULL)
	{
		ft_save_var(&var_list, *environ, 1);
		environ++;
	}
	ft_save_var(&var_list, "?=0", 0);
	return (var_list);
}

void	check_eof(char *line, t_list *var_list)
{
	if (line)
		return ;
	printf("exit\n");
	ft_clear_vars(var_list);
	exit(g_exit_status);
}

int	main(void)
{
	char		*prompt;
	char		*input;
	t_tlist		*tokens;
	t_list		*var_list;

	var_list = save_var();
	ft_change_lvl(&var_list, 1);
	while (1)
	{
		tokens = NULL;
		sig_init();
		prompt = create_prompt();
		input = readline(prompt);
		if (input)
			add_history(input);
		check_eof(input, var_list);
		input = preparse(input);
		if (input)
		{
			lexer(input, &tokens, &var_list);
			ft_start(tokens, &var_list);
		}
		ft_add_status(&var_list);
		clear_all(input, tokens, prompt);
	}
}
