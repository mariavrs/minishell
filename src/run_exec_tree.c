/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exec_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 20:26:56 by mvorslov          #+#    #+#             */
/*   Updated: 2023/01/25 20:01:24 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

void	run_exec(t_exec *cmd, int *exit_status)
{
	*exit_status = 0;
	if (!ft_strncmp(cmd->argv[0], "cd", 2))
		ft_cd();
	else if (!ft_strncmp(cmd->argv[0], "echo", 4))
		ft_echo();
	else if (!ft_strncmp(cmd->argv[0], "env", 3))
		ft_env();
	else if (!ft_strncmp(cmd->argv[0], "exit", 4))
		ft_exit();
	else if (!ft_strncmp(cmd->argv[0], "export", 6))
		ft_export();
	else if (!ft_strncmp(cmd->argv[0], "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(cmd->argv[0], "unset", 5))
		ft_unset();
	else
	{
		printf("minishell: %s: command not found :(\n", cmd->argv[0]);
		*exit_status = 127;
	}
}

void	run_redir(t_redir *cmd, int *exit_status)
{
	(void)cmd;
	(void)exit_status;
}

void	run_pipe(t_pipe *cmd, int *exit_status)
{
	(void)cmd;
	(void)exit_status;
}

void	run_list(t_lol *cmd, int *exit_status)
{
	ft_exec_tree(cmd->left, exit_status);
	if (*exit_status && cmd->mode == '|')
		ft_exec_tree(cmd->right, exit_status);
	else if (!(*exit_status) && cmd->mode == '&')
		ft_exec_tree(cmd->right, exit_status);
}
