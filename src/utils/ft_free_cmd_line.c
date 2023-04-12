/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_cmd_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:27:19 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/12 00:14:56 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

void	ft_free_redir(t_redir **rdr)
{
	while (*rdr)
		ft_free_redir_elem(rdr);
}

void	ft_free_cmd(t_cmd **cmd)
{
	while (*cmd)
		ft_free_cmd_elem(cmd);
}

void	ft_free_cmd_list(t_block **cmd_block)
{
	while (*cmd_block)
		ft_free_cmd_list_elem(cmd_block);
}

void	ft_free_exit(t_msh *msh)
{
	ft_free_cmd_list(&msh->cmd_list);
	ft_free_str(&msh->sline);
	ft_free_str(&msh->ex_sline);
	ft_free_str(&msh->prompt);
	ft_free_dbl_str(&msh->envp);
	ft_free_dbl_str(&msh->envp_lcl);
	rl_clear_history();
}
