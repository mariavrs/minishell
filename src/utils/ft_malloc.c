/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:58:04 by mvorslov          #+#    #+#             */
/*   Updated: 2023/03/31 11:22:55 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

extern int	g_exit_status;

char	*ft_malloc_str(int size)
{
	char	*str;

	str = NULL;
	str = malloc(sizeof(char) * size);
	if (!str)
		return (g_exit_status = 1, ft_putstr_fd("minishell: malloc error\n", 2),
			NULL);
	ft_bzero(str, size);
	return (str);
}
