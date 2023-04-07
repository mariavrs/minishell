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
