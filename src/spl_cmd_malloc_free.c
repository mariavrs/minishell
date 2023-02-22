/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_malloc_free.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:27:19 by mvorslov          #+#    #+#             */
/*   Updated: 2023/02/22 17:37:51 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

int	ft_malloc_spl_cmd(t_spl_cmd *cmd, int argc, int redirc)
{
	cmd->argv = NULL;
	cmd->redir = NULL;
	cmd->argv = malloc(sizeof(char *) * (argc + 1));
	if (!cmd->argv)
		return (1);
	cmd->redir = malloc(sizeof(t_redir) * redirc);
	if (!cmd->redir)
		return (free(cmd->argv), 1);//print error
	cmd->argv[argc] = NULL;
	cmd->argc = argc;
	cmd->redirc = redirc;
	return (0);
}

void	ft_free_redir_info(t_spl_cmd *cmd)
{
	if (!cmd->redir)
		return ;
	while (--cmd->redirc >= 0)
	{
		free(cmd->redir[cmd->redirc].file);
		cmd->redir[cmd->redirc].file = NULL;
	}
	free(cmd->redir);
	cmd->redir = NULL;
}

void	ft_free_argv(t_spl_cmd *cmd)
{
	if (!cmd->argv)
		return ;
	cmd->argc++;
	while (--cmd->argc >= 0)
	{
		free(cmd->argv[cmd->argc]);
		cmd->argv[cmd->argc] = NULL;
	}
	free(cmd->argv);
	cmd->argv = NULL;
}
