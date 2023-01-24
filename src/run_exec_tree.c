/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exec_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 20:26:56 by mvorslov          #+#    #+#             */
/*   Updated: 2023/01/24 21:26:23 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

void	run_exec(t_exec *cmd, int exit_status)
{
	(void)cmd;
	(void)exit_status;
}

void	run_redir(t_redir *cmd, int exit_status)
{
	(void)cmd;
	(void)exit_status;
}

void	run_pipe(t_pipe *cmd, int exit_status)
{
	(void)cmd;
	(void)exit_status;
}

void	run_list(t_list *cmd, int exit_status)
{
	ft_exec_tree(cmd->left, exit_status);
	if (exit_status == cmd->mode)
		ft_exec_tree(cmd->right, exit_status);
}
