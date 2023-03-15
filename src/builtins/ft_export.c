/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/03/14 23:25:16 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

static int	is_valid(char *str)
{
	if (str[0] >= '0' && str[0] <= '9')
		return (1);
	while (*str)
	{
		if (!((*str >= 'a' && *str <= 'z')
				|| (*str >= 'A' && *str <= 'Z')
				|| *str == '_'
				|| (*str >= '0' && *str <= '9')))
			return (1);
		str++;
	}
	return (0);
}

int	pos_sep(char *str)
{
	int	i;

	i = -1;
	while (++i < (int)ft_strlen(str))
		if (str[i] == '=')
			return (i + 1);
	return (0);
}

static void	exp_error(char *var)
{
	ft_putstr_fd("export: ", 2);
	write(2, "\'", 1);
	ft_putstr_fd(var, 2);
	write(2, "\'", 1);
	ft_putstr_fd(": not a valid identifier\n", 2);
}

static void	export_env_print(t_msh *msh)
{
	int		i;
	char	*var;
	char	*value;

	i = -1;
	value = NULL;
	while (msh->envp[++i])
	{
		write(1, "declare -x ", 11);
		var = ft_substr(msh->envp[i], 0, pos_sep(msh->envp[i]) - 1);
		if (pos_sep(msh->envp[i]) <= (int)ft_strlen(msh->envp[i]))
			value = ft_strdup(msh->envp[i] + pos_sep(msh->envp[i]));
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
		ft_free_str(&value);
	}
}

int	ft_export(t_msh *msh, char **inputs)
{
	int		i;
	t_env	env;
	char	*e_var;

	i = 0;
	if (!inputs[1])
		return (export_env_print(msh), 0);
	while (inputs[++i])
	{
		e_var = ft_substr(inputs[i], 0, pos_sep(inputs[i]) - 1);
		if (!is_valid(e_var))
		{
			env.full_var = ft_strdup(inputs[i]);
			env.name_ln = ft_strlen(inputs[i]) - pos_sep(inputs[i]);
			env.i = find_in_envp(env, msh->envp);
			if (env.i >= 0)
				env_lcl_replace(env, msh->envp);
			else
				env_lcl_add(env, msh, msh->envp, 1);
		}
		else
			exp_error(e_var);
		ft_free_str(&e_var);
	}
	return (0);
}
