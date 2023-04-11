/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:58:04 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/11 17:18:33 by mvorslov         ###   ########.fr       */
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
		return (malloc_error(), NULL);
	ft_bzero(str, size);
	return (str);
}

char	**ft_malloc_dbl_str(int size)
{
	char	**str;

	str = NULL;
	str = malloc(sizeof(char *) * size);
	if (!str)
		return (malloc_error(), NULL);
	while (size >= 0)
		str[size--] = NULL;
	return (str);
}
