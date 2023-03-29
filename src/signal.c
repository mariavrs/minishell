/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:34:08 by ede-smet          #+#    #+#             */
/*   Updated: 2023/03/29 20:49:51 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

extern pid_t	g_pid;

void	ctrl_c_handler(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
}

void	ctrl_d_handler(int sig)
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
	if (g_pid != 0)
	{
		ft_putendl_fd("Quit (core dumped)", 1);
		kill(g_pid, SIGQUIT);
		g_pid = 0;
	}
}

void	sig_handler(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, &ctrl_d_handler);
		signal(SIGQUIT, &ctrl_bslash_handler);
	}
	if (sig == 2)
	{
		signal(SIGINT, &ctrl_c_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 3)
	{
		printf("exit\n");
		exit(0);
	}
}
