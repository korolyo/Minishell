/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:38:28 by acollin           #+#    #+#             */
/*   Updated: 2021/10/09 12:01:13 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 130;
	}
}

void	sig_handler3(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		g_exit_status = 130;
	}
	if (signum == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		g_exit_status = 131;
	}
}

void	catch_heredoc_sig(void)
{
	signal(SIGINT, sig_handler3);
	signal(SIGQUIT, sig_handler3);
}

void	sig_init(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	interrupt_here_document(int signal)
{
	(void)signal;
	g_exit_status = 130;
	exit(130);
}
