/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/02 17:03:35 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

int	ft_unset(t_msh *msh, char **inputs)
{
	int	i;

	i = 0;
	while (inputs[++i])
	{
		if (!(ft_strlen(inputs[i]) == 1 && inputs[i][0] == '_'))
		{
			if (env_del(msh, &msh->envp, inputs[i]))
				return (1);
			if (env_del(msh, &msh->envp_lcl, inputs[i]))
				return (1);
		}
	}
	return (0);
}
