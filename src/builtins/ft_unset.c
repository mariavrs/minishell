/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/05 15:09:22 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

int	ft_unset(t_msh *msh)
{
	int		i;

	i = 0;
	while (msh->argv[++i])
	{
		if (!(ft_strlen(msh->argv[i]) == 1 && msh->argv[i][0] == '_'))
		{
			if (env_del(msh, msh->argv[i]))
				return (1);
		}
	}
	return (0);
}
