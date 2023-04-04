/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/04 21:36:01 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

int	ft_unset(t_msh *msh, char **inputs)
{
	int		i;

	i = 0;
	while (inputs[++i])
	{
		if (!(ft_strlen(inputs[i]) == 1 && inputs[i][0] == '_'))
		{
			if (env_del(msh, inputs[i]))
				return (1);
		}
	}
	return (0);
}
