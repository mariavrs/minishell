/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:34:08 by ede-smet          #+#    #+#             */
/*   Updated: 2023/03/31 00:48:38 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

extern pid_t	g_pid;
extern int		g_khd;

void	ctrl_c_handler(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	kill(1, SIGINT);
}

void	clear_line_handler(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ctrl_bslash_handler(int sig)
{
	(void)sig;
	ft_putendl_fd("Quit (core dumped)", 1);
}

void	signal_manager(int flag)
{
	if (flag == 1)
	{
		signal(SIGINT, &clear_line_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (flag == 2)
	{
		signal(SIGINT, &ctrl_c_handler);
		signal(SIGQUIT, &ctrl_bslash_handler);
	}
}
