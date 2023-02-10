/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 23:26:27 by mvorslov          #+#    #+#             */
/*   Updated: 2023/02/10 23:26:31 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

void	redir_in(t_spl_cmd *cmd, int i)
{
	if (!cmd->stdin_cpy)
		cmd->stdin_cpy = dup(STDIN_FILENO);
	if (cmd->redir[i].mode == '<')
		cmd->redir[i].fd = open(cmd->redir[i].file, O_RDONLY);
/* 	else if (cmd->redir[i].mode == '-')
		readline() or idk */
	dup2(cmd->redir[i].fd, STDIN_FILENO);
}

void	redir_out(t_spl_cmd *cmd, int i)
{
	if (!cmd->stdout_cpy)
		cmd->stdout_cpy = dup(STDOUT_FILENO);
	if (cmd->redir[i].mode == '>')
		cmd->redir[i].fd = open(cmd->redir[i].file, O_CREAT | O_WRONLY, 0664);
	else if (cmd->redir[i].mode == '+')
		cmd->redir[i].fd = open(cmd->redir[i].file, O_CREAT | O_APPEND | O_WRONLY, 0664);
	dup2(cmd->redir[i].fd, STDOUT_FILENO);
}

void	redir_clean(t_spl_cmd *cmd)
{
	if (cmd->stdin_cpy)
	{
		dup2(cmd->stdin_cpy, STDIN_FILENO);
		close(cmd->stdin_cpy);
	}
	if (cmd->stdout_cpy)
	{
		dup2(cmd->stdout_cpy, STDOUT_FILENO);
		close(cmd->stdout_cpy);
	}
}
