/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:34:08 by ede-smet          #+#    #+#             */
/*   Updated: 2023/03/31 16:43:40 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

extern int	g_exit_status;

void	ctrl_c_handler(int sig)
{
	g_exit_status = 128 + sig;
	ft_putchar_fd('\n', 1);
}

void	clear_line_handler(int sig)
{
	(void)sig;
	g_exit_status = 128 + sig;
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ctrl_bslash_handler(int sig)
{
	g_exit_status = 128 + sig;
	ft_putendl_fd("Quit (core dumped)", 1);
}

void	signal_manager(int mode)
{
	if (mode == MODE_NITR)
	{
		signal(SIGINT, &ctrl_c_handler);
		signal(SIGQUIT, &ctrl_bslash_handler);
	}
	else if (mode == MODE_INTR_CMD)
	{
		signal(SIGINT, &clear_line_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == MODE_INTR_HDC)
	{
		signal(SIGINT, &clear_line_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}
