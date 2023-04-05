/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/05 15:09:51 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

static void	ft_print_line(char **input, int i)
{
	ft_putstr_fd(input[i], 1);
	if (input[i + 1])
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

int	ft_echo(t_msh *msh)
{
	int	i;

	i = 1;
	if (!msh->argv)
		return (1);
	while (msh->argv[i] && !option_control(msh->argv[i]))
		i++;
	if (i != 1)
		while (msh->argv[i])
			ft_print_line(msh->argv, i++);
	else
	{
		while (msh->argv[i])
			ft_print_line(msh->argv, i++);
		ft_putchar_fd('\n', 1);
	}
	return (0);
}
