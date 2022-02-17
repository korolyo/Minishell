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

//#include "minishell.h"
//
//void	sig_handler(int signum)
//{
//	if (signum == SIGINT)
//	{
//		write(1, "\n", 1);
//		rl_replace_line("", 0);
//		rl_on_new_line();
//		rl_redisplay();
//	}
//}
//
//void	sig_init(void)
//{
//	signal(SIGINT, sig_handler);
//	signal(SIGQUIT, SIG_IGN);
//}
