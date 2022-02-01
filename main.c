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
<<<<<<< HEAD
	(void)argc;
	(void)argv;
	(void)envp;

	prompt = readline("minishell >");
	prompt = preparse(prompt);
	lexer(prompt);
//	if (*prompt)
//		prompt = parse_line(prompt, envp);
//	printf("main check \n");
=======
	t_tlist		tokens;
	(void)argc;
	(void)argv;

	prompt = readline("minishell >");
	prompt = preparse(prompt);
	tokenization(&tokens, prompt);
	if (*prompt)
		prompt = parse_line(prompt, envp);
>>>>>>> aac3de6956a0406042df3c0d7ac8715c229f056e
	printf("%s\n", prompt);
	add_history(prompt);
	clear_all(prompt);
	exit(EXIT_SUCCESS);
}
