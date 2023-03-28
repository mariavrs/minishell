/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:27:19 by mvorslov          #+#    #+#             */
/*   Updated: 2023/03/27 16:45:49 by mvorslov         ###   ########.fr       */
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

void	ft_free_spl_cmd(t_msh *msh)
{
	if (!msh)
		return ;
	ft_free_str(&msh->spl_cmd);
	ft_free_dbl_str(&msh->argv);
}

void	ft_free_exit(t_msh *msh)
{
	ft_free_spl_cmd(msh);
	ft_free_str(&msh->sline);
	ft_free_str(&msh->ex_sline);
	ft_free_dbl_str(&msh->envp);
	ft_free_dbl_str(&msh->envp_lcl);
	rl_clear_history();
}
