/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_cmd_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:27:19 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/09 04:20:40 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

void	ft_free_redir(t_redir **rdr)
{
	t_redir	*next;

	while (*rdr)
	{
		next = (*rdr)->next;
		ft_free_str(&(*rdr)->filename);
		free(*rdr);
		*rdr = next;
	}
}

void	ft_free_cmd(t_cmd **cmd)
{
	t_cmd	*next;

	while (*cmd)
	{
		next = (*cmd)->next;
		ft_free_str(&(*cmd)->spl_cmd);
		ft_free_dbl_str(&(*cmd)->argv);
		ft_free_redir(&(*cmd)->rdr);
		free(*cmd);
		*cmd = next;
	}
}

void	ft_free_cmd_list(t_block **cmd_block)
{
	t_block	*next;

	while (*cmd_block)
	{
		next = (*cmd_block)->next;
		ft_free_cmd(&(*cmd_block)->pipeline);
		free(*cmd_block);
		*cmd_block = next;
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
