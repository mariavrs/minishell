/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:58:04 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/12 21:24:25 by mvorslov         ###   ########.fr       */
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
	while (--size >= 0)
		str[size] = NULL;
	return (str);
}

void	malloc_error(void)
{
	g_exit_status = ERR_MALLOC;
	ft_putendl_fd("minishell: malloc error", 2);
	ft_putendl_fd("not enough heap memory to perform execution", 2);
}
