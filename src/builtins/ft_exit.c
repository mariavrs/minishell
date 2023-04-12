/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/13 00:57:55 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

extern int	g_exit_status;

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

void	ft_exit_error(int exit_flag, char *str, t_msh *msh, int code)
{
	if (!msh->pipe_flag)
		ft_putendl_fd("exit", 1);
	if (exit_flag == 1)
		ft_mini_perror("exit", NULL, "too many arguments", 1);
	if (exit_flag == 2)
		ft_mini_perror("exit", str, "numeric argument required", 1);
	if (exit_flag != 1)
		ft_free_exit(msh);
	if (!msh->pipe_flag && exit_flag != 1)
		exit(code);
	else
		g_exit_status = code;
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

int	ft_exit(t_msh *msh, char **argv)
{
	long long int	i;
	int				mod;

	if (!argv)
		return (1);
	if (!argv[1])
		return (ft_exit_error(0, NULL, msh, g_exit_status),
			g_exit_status);
	i = ft_ll_atoi(argv[1]);
	mod = i % 256;
	if (!is_numeric(argv[1]) && argv[2])
		return (ft_exit_error(1, NULL, msh, 1), 1);
	else if (border_llong_check(argv[1]) || is_numeric(argv[1]))
		return (ft_exit_error(2, argv[1], msh, 2), 2);
	else if (i < 0)
		return (ft_exit_error(0, NULL, msh, 256 + mod), 256 + mod);
	else if (i > 255)
		return (ft_exit_error(0, NULL, msh, mod), mod);
	else
		return (ft_exit_error(0, NULL, msh, (int)i), (int)i);
	return (0);
}
