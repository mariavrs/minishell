/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/03/30 01:38:55 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

static int	is_valid(char *str)
{
	int	i;
	int	flag;

	flag = 1;
	i = 0;
	if (str[0] >= '0' && str[0] <= '9')
		return (1);
	while (str[i] && flag && str[i] != '=')
	{
		if (str[i] == '+' || str[i] != '=')
		{
			if (str[i] == '+' && str[i + 1] && str[i + 1] == '=')
				flag = 0;
			else if (str[i] == '+')
				return (1);
			else if (!((str[i] >= 'a' && str[i] <= 'z')
					|| (str[i] >= 'A' && str[i] <= 'Z')
					|| str[i] == '_'
					|| (str[i] >= '0' && str[i] <= '9')))
				return (1);
		}
		i++;
	}
	return (0);
}

static void	exp_error(char *var, char *check, int *flag)
{
	if (!check)
		return (ft_putstr_fd("minishell: malloc error\n", 2));
	ft_putstr_fd("export: ", 2);
	write(2, "\'", 1);
	ft_putstr_fd(var, 2);
	write(2, "\'", 1);
	ft_putstr_fd(": not a valid identifier\n", 2);
	*flag = 1;
}

static void	export_env_print(t_msh *msh)
{
	int		i;
	char	*var;
	char	*value;

	i = -1;
	while (msh->envp[++i])
	{
		var = ft_substr(msh->envp[i], 0, pos_sep(msh->envp[i]) - 1);
		if (!var)
			return (ft_putstr_fd("minishell: malloc error\n", 2));
		write(1, "declare -x ", 11);
		if (pos_sep(msh->envp[i]) <= (int)ft_strlen(msh->envp[i]))
			value = msh->envp[i] + pos_sep(msh->envp[i]);
		write(1, var, ft_strlen(var));
		if (value && pos_sep(msh->envp[i]))
		{
			write(1, "=\"", 2);
			write(1, value, ft_strlen(value));
			write(1, "\"\n", 2);
		}
		else
			write(1, "\n", 1);
		ft_free_str(&var);
	}
}

int	ft_export(t_msh *msh, char **inputs)
{
	t_env	env;
	int		err_flag;
	int		i;

	env.name_ln = -1;
	err_flag = 0;
	i = 0;
	if (!inputs[1])
		return (export_env_print(msh), 0);
	while (inputs[++i])
	{
		if (!is_valid(inputs[i]) && *inputs[i] != '+' && *inputs[i] != '=')
		{
			if (get_and_put_var(&env, msh, inputs[i]))
				return (1);
		}
		else
			exp_error(inputs[i], " ", &err_flag);
	}
	return (err_flag);
}
