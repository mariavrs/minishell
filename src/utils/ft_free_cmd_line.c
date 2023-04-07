/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_cmd_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:27:19 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/01 13:48:37 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

void	ft_free_cmd(t_cmd **cmd)
{
	if (!(*cmd))
		return ;
	ft_free_str(&(*cmd)->spl_cmd);
	ft_free_dbl_str(&(*cmd)->argv);
	free(*cmd);
	*cmd = NULL;
}

void	ft_free_pipeline(t_cmd **cmd)
{
	t_cmd	*tmp;

	while (*cmd)
	{
		tmp = (*cmd)->next;
		ft_free_cmd(&(*cmd));
		*cmd = tmp;
	}
}

void	ft_free_cmd_list_block(t_block	**cmd_block)
{
	if (!(*cmd_block))
		return ;
	ft_free_pipeline(&(*cmd_block)->pipeline);
	free(*cmd_block);
	*cmd_block = NULL;
}

void	ft_free_cmd_list(t_block	**cmd_block)
{
	t_block	*tmp;

	while (*cmd_block)
	{
		tmp = (*cmd_block)->next;
		ft_free_cmd_list_block(&(*cmd_block));
		*cmd_block = tmp;
	}
}

void	ft_free_exit(t_msh *msh)
{
	ft_free_cmd_list(&msh->cmd_list);
	ft_free_str(&msh->sline);
	ft_free_str(&msh->ex_sline);
	ft_free_dbl_str(&msh->envp);
	ft_free_dbl_str(&msh->envp_lcl);
	rl_clear_history();
}
