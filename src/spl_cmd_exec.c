/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 23:25:09 by mvorslov          #+#    #+#             */
/*   Updated: 2023/02/25 16:02:11 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

void	run_exec(t_spl_cmd *cmd, t_msh *msh)
{
	if (!ft_strncmp(cmd->argv[0], "cd", 3))
		msh->exit_status = ft_cd(cmd->argv, msh);
	else if (!ft_strncmp(cmd->argv[0], "echo", 5))
		msh->exit_status = ft_echo(cmd->argv);
	else if (!ft_strncmp(cmd->argv[0], "env", 4))
		msh->exit_status = ft_env(*msh);
	else if (!ft_strncmp(cmd->argv[0], "exit", 5))
		msh->exit_status = ft_exit(cmd->argv, msh);
	else if (!ft_strncmp(cmd->argv[0], "export", 7))
		msh->exit_status = ft_export(msh, cmd->argv);
	else if (!ft_strncmp(cmd->argv[0], "pwd", 4))
		msh->exit_status = ft_pwd();
	else if (!ft_strncmp(cmd->argv[0], "unset", 6))
		msh->exit_status = ft_unset(msh, cmd->argv);
	else if (search_bin(cmd->argv, msh))
	{
		printf("minishell: %s: command not found\n", cmd->argv[0]);
		msh->exit_status = 127;
	}
}

void	run_spl_cmd(t_spl_cmd *cmd, t_msh *msh)
{
	int	i;

	i = -1;
	msh->exit_status = 0;
	while (++i < cmd->redirc && msh->exit_status == 0)
	{
		if (cmd->redir[i].mode == '>' || cmd->redir[i].mode == '+')
			msh->exit_status = redir_out(cmd, i);
		else
			msh->exit_status = redir_in(cmd, i, msh);
		close(cmd->redir[i].fd);
	}
	ft_free_redir_info(cmd);
	if (msh->exit_status == 0)
		run_exec(cmd, msh);
	ft_free_argv(cmd);
	redir_clean(cmd);
}
