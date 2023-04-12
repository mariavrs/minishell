/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 23:45:04 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/12 18:29:14 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

extern int	g_exit_status;

char	*cmd_error_msg(char *s1, char *s2, char *err_msg, t_msh *msh)
{
	int		len;
	char	*msg;

	len = ft_strlen(s1) + ft_strlen(err_msg) + 3;
	if (s2)
		len += ft_strlen(s2) + 2;
	msg = ft_malloc_str(len);
	if (!msg)
	{
		ft_putendl_fd("exit", 2);
		return (ft_free_exit(msh), exit(ERR_MALLOC), NULL);
	}
	ft_strlcpy(msg, s1, ft_strlen(s1) + 1);
	len = ft_strlen(s1) + 2;
	ft_strlcpy(&msg[len - 2], ": ", 3);
	if (s2)
	{
		ft_strlcpy(&msg[len], s2, ft_strlen(s2) + 1);
		len += ft_strlen(s1) + 2;
		ft_strlcpy(&msg[len - 2], ": ", 3);
	}
	ft_strlcpy(&msg[len], err_msg, ft_strlen(err_msg) + 1);
	return (msg);
}

void	ft_mini_perror(char *s1, char *s2, char *err_msg, int print_msh)
{
	if (print_msh)
		ft_putstr_fd("minishell: ", 2);
	if (s1)
	{
		ft_putstr_fd(s1, 2);
		ft_putstr_fd(": ", 2);
	}
	if (s2)
	{
		ft_putstr_fd(s2, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(err_msg, 2);
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
		return (ft_mini_perror("cd", NULL, "too many arguments", 1), 1);
	if (if_not_exist(msh, "HOME", ENV_EXP)
		&&if_not_exist(msh, "HOME", ENV_LCL) && !argv[1])
		return (ft_mini_perror("cd", NULL, "HOME not set", 1), 1);
	return (0);
}

void	error_export(char *var, int *flag)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(var, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	*flag = 1;
}
