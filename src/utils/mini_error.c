/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 23:45:04 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/07 16:39:53 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

void	malloc_error(void)
{
	ft_putstr_fd("minishell: malloc error\n", 2);
}

void	ft_mini_perror(char *argv, char *err_msg, int print_msh)
{
	if (print_msh)
		ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(err_msg, 2);
}

void	error_unexpected_token(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (*str == '\n')
		write(2, "newline", 7);
	else
	{
		write(2, str++, 1);
		if (*str == *(str - 1))
			write(2, str, 1);
	}
	write(2, "\'\n", 2);
}

int	error_cd(t_msh *msh, char **argv, char *home)
{
	if (!home)
		return (malloc_error(), 1);
	if (!argv)
		return (1);
	if (dbl_str_size(argv) > 2)
		return (ft_putendl_fd("minishell: cd: too many arguments", 2), 1);
	if (if_not_exist(msh, "HOME", ENV_EXP)
		&&if_not_exist(msh, "HOME", ENV_LCL) && !argv[1])
		return (ft_putendl_fd("minishell: cd: HOME not set", 2), 1);
	return (0);
}

void	error_export(char *var, int *flag)
{
	ft_putstr_fd("minishell: export: ", 2);
	write(2, "\'", 1);
	ft_putstr_fd(var, 2);
	write(2, "\'", 1);
	ft_putstr_fd(": not a valid identifier\n", 2);
	*flag = 1;
}
