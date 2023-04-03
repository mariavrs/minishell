/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_hdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 19:02:39 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/03 14:56:05 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

void	ctrl_c_heredoc_handler(int sig)
{
	rl_clear_history();
	ft_putchar_fd('\n', 1);
	exit (128 + sig);
}

void	ctrl_c_heredoc_pipe_handler(int sig)
{
	rl_clear_history();
	exit (128 + sig);
}
