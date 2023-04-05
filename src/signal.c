/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:34:08 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/02 19:03:10 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

extern int	g_exit_status;

void	ctrl_c_noninter_handler(int sig)
{
	g_exit_status = 128 + sig;
	ft_putchar_fd('\n', 1);
}

void	ctrl_c_prompt_handler(int sig)
{
	g_exit_status = 128 + sig;
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ctrl_c_heredoc_handler(int sig)
{
	rl_clear_history();
	ft_putchar_fd('\n', 1);
	exit (128 + sig);
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
		signal(SIGINT, &ctrl_c_noninter_handler);
		signal(SIGQUIT, &ctrl_bslash_handler);
	}
	else if (mode == MODE_INTR_CMD)
	{
		signal(SIGINT, &ctrl_c_prompt_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == MODE_INTR_HDC)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
