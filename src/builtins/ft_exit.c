/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/03/01 20:44:05 by ede-smet         ###   ########.fr       */
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

static int	border_llong_check(char *str)
{
	if (str[0] == '+' || ft_isdigit(str[0]))
	{
		if (ft_ll_atoi(str) < 0)
			return (1);
	}
	else
		if (ft_ll_atoi(str) > 0)
			return (1);
	return (0);
}

int	ft_exit(char **input, t_msh *msh)
{
	long long int	i;
	int				mod;

	if (!input)
		return (1);
	if (!input[1])
		return (exit_error(-1, NULL), ft_free_exit(msh)
			, exit(msh->exit_status), msh->exit_status);
	i = ft_ll_atoi(input[1]);
	mod = i % 256;
	if (!is_numeric(input[1]) && input[2])
		return (exit_error(0, NULL), 1);
	else if (border_llong_check(input[1]) || is_numeric(input[1]))
		return (exit_error(1, input[1]), ft_free_exit(msh), exit(2), 2);
	else if (i < 0)
		return (exit_error(-1, NULL),
			ft_free_exit(msh), exit(256 + mod), 256 + mod);
	else if (i > 255)
		return (exit_error(-1, NULL), ft_free_exit(msh), exit(mod), mod);
	else
		return (exit_error(-1, NULL), ft_free_exit(msh), exit((int)i), (int)i);
	return (0);
}
