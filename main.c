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

void	clear_all(char *prompt)
{
	free(prompt);
}

int	main(int argc, char **argv, char **envp)
{
	char		*prompt;
	t_tlist		tokens;
	(void)argc;
	(void)argv;

	prompt = readline("minishell >");
	prompt = preparse(prompt);
	tokenization(&tokens, prompt);
	if (*prompt)
		prompt = parse_line(prompt, envp);
	printf("%s\n", prompt);
	add_history(prompt);
	clear_all(prompt);
	exit(EXIT_SUCCESS);
}
