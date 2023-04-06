/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/02 22:20:08 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

int	ft_env(t_msh *msh, char **argv, int mode)
{
	int		i;

	(void)argv;
	i = -1;
	if (mode == 1)
		while (msh->envp[++i])
			ft_putendl_fd(msh->envp[i], 1);
	else
	{
		while (msh->envp[++i])
			if (ft_strncmp(msh->envp[i] + pos_sep(msh->envp[i]), "\"\"\0", 3)
				&& pos_sep(msh->envp[i]))
				ft_putendl_fd(msh->envp[i], 1);
	}
	return (0);
}
