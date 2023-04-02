/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/02 18:31:30 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

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
	while (inputs[++i] && !err_flag)
	{
		err_flag = get_and_put_var(&env, msh, inputs[i]);
		if (err_flag == -1)
			exp_error(inputs[i], " ", &err_flag);
	}
	return (err_flag);
}
