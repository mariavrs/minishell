/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/03/19 13:22:17 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

static void	ft_print_line(char **input, int i)
{
	ft_putstr_fd(input[i], 1);
	if (input[i + 1])
		ft_putstr_fd(" ", 1);
}

int	ft_echo(char *input[])
{
	int	i;

	i = 1;
	if (!input)
		return (1);
	if (ft_strlen(input[i]) == 2 && !ft_strncmp(input[i], "-n", 2))
		while (input[++i])
			ft_print_line(input, i);
	else
	{
		while (input[i])
			ft_print_line(input, i++);
		ft_putchar_fd('\n', 1);
	}
	return (0);
}
