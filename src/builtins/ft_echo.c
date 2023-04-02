/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/02 17:21:15 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

static void	ft_print_line(char **input, int i)
{
	ft_putstr_fd(input[i], 1);
	if (input[i][0] != '\0' && input[i + 1] && input[i + 1][0] != '\0')
		ft_putstr_fd(" ", 1);
}

static int	option_control(char *str)
{
	if (*str == '-')
		str++;
	if (!*str)
		return (1);
	while (*str)
	{
		if (*str == 'n')
			str++;
		else
			return (1);
	}
	return (0);
}

int	ft_echo(char *input[])
{
	int	i;

	i = 1;
	if (!input)
		return (1);
	while (input[i] && !option_control(input[i]))
		i++;
	if (i != 1)
		while (input[i])
			ft_print_line(input, i++);
	else
	{
		while (input[i])
			ft_print_line(input, i++);
		ft_putchar_fd('\n', 1);
	}
	return (0);
}
