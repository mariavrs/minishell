/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/03/19 23:38:50 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

static int	is_valid(char *str)
{
	int	i;

	i = 0;
	if (str[0] >= '0' && str[0] <= '9')
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!((str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z')
				|| str[i] == '_'
				|| (str[i] >= '0' && str[i] <= '9')))
			return (1);
		i++;
	}
	return (0);
}

static void	exp_error(char *var, char *check)
{
	int	i;

	i = 0;
	if (!check)
		return (ft_putstr_fd("minishell: malloc error\n", 2));
	ft_putstr_fd("export: ", 2);
	write(2, "\'", 1);
	while (var[i] && var[i] != '=')
	{
		ft_putchar_fd(var[i], 2);
		i++;
	}
	write(2, "\'", 1);
	ft_putstr_fd(": not a valid identifier\n", 2);
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

void	replace_if_value(t_env *env, t_msh *msh, char *input)
{
	if (pos_sep(input))
		env_lcl_replace(*env, msh->envp);
	else
		ft_free_str(&env->full_var);
}

int	ft_export(t_msh *msh, char **inputs)
{
	int		i;
	t_env	env;

	i = 0;
	if (!inputs[1])
		return (export_env_print(msh), 0);
	while (inputs[++i])
	{
		env.full_var = ft_strdup(inputs[i]);
		if (env.full_var && !is_valid(inputs[i]))
		{
			env.name_ln = 0;
			while (inputs[i][env.name_ln] && inputs[i][env.name_ln] != '=')
				env.name_ln++;
			env.i = find_in_envp(env, msh->envp);
			if (env.i >= 0)
				replace_if_value(&env, msh, inputs[i]);
			else if (env.i < 0)
				env_lcl_add(env, msh, msh->envp, 1);
		}
		else
			return (exp_error(inputs[i], env.full_var), 1);
	}
	return (0);
}
