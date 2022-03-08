/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:41:28 by acollin           #+#    #+#             */
/*   Updated: 2021/10/06 20:42:12 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include <unistd.h>
# include <signal.h>

/*
 * Global variable for hosting exit status
 */
int		g_exit_status;

void	sig_handler(int signum);
void	sig_init(void);
void	sig_handler3(int signum);
void	catch_heredoc_sig(void);
void	interrupt_here_document(int signal);
void	check_eof(char *line, t_list *var_list);

#endif
