/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/02/24 23:58:47 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

static int	is_numeric(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (1);
		str++;
	}
	return (0);
}

static void	exit_error(int i, char *str)
{
	ft_putstr_fd("exit\n", 1);
	if (i == 0)
		ft_putstr_fd("exit: too many arguments\n", 2);
	if (i == 1)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
}

int	ft_exit(char **input, t_msh *msh)
{
	double	i;

	if (!input)
		return (1);
	if (!input[1])
		return (exit_error(-1, NULL), exit(msh->exit_status), msh->exit_status);
	i = ft_atoi(input[1]);
	if (!is_numeric(input[1]) && input[2])
		return (exit_error(0, NULL), 1);
	else if (i > (double)LLONG_MAX || is_numeric(input[1]))
		return (exit_error(1, input[1]), exit(2), 2);
	else if (i < 0)
		return (exit_error(-1, NULL), exit(256 + (long long int)i % 256), 256 - (long long int)i % 256);
	else if (i > 255)
		return (exit_error(-1, NULL), exit((long long int)i % 256), (long long int)i % 256);
	else
		return (exit_error(-1, NULL), exit(i), i);
	return (0);
}
