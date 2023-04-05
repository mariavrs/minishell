/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:27:19 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/01 13:48:37 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

void	ft_free_str(char **str)
{
	if (!(*str))
		return ;
	ft_bzero(*str, ft_strlen(*str));
	free(*str);
	*str = NULL;
}

void	ft_free_dbl_str(char ***str)
{
	int	i;

	i = 0;
	if (!(*str))
		return ;
	while ((*str)[i])
	{
		ft_bzero((*str)[i], ft_strlen((*str)[i]));
		free((*str)[i]);
		(*str)[i] = NULL;
		i++;
	}
	free(*str);
	*str = NULL;
}

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
	t_cmd *tmp;

	tmp = *cmd;
	while (*cmd)
	{
		tmp = (*cmd)->next;
		ft_free_cmd(&(*cmd));
		*cmd = tmp;
	}
}

void	ft_free_exit(t_msh *msh)
{
	ft_free_pipeline(&msh->pipeline);
	ft_free_str(&msh->sline);
	ft_free_str(&msh->ex_sline);
	ft_free_dbl_str(&msh->envp);
	ft_free_dbl_str(&msh->envp_lcl);
	rl_clear_history();
}
