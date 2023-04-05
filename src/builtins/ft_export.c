/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/05 15:06:58 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

static int	get_name_lenght(char *line)
{
	int	i;

	i = 0;
	while (is_valid_varname(line[i]) && !ft_isdigit(line[0]))
		i++;
	if (line[i] == '=' || !ft_strncmp(&line[i], "+=", 2) || line[i] == '\0')
		return (i);
	return (-1);
}

static int	get_and_put_var(t_env *env, t_msh *msh, char *name)
{
	env->name_ln = get_name_lenght(name);
	if (env->name_ln >= 0)
	{
		env->name = name;
		env->mod = get_env_mod(name[env->name_ln]);
		env->value = name + env->name_ln + env->mod + 1;
		if (get_full_var_str(name, env, msh))
			return (1);
		if (env->src == ENV_LCL)
			if (del(msh, *env, msh->envp_lcl))
				return (1);
		env->dest = ENV_EXP;
		if (put_env_var(env, msh))
			return (1);
	}
	else
		return (-1);
	return (0);
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

int	ft_export(t_msh *msh)
{
	t_env	env;
	int		err_flag;
	int		i;

	env.name_ln = -1;
	err_flag = 0;
	i = 0;
	if (!msh->argv[1])
		return (export_env_print(msh), 0);
	while (msh->argv[++i])
	{
		if (get_and_put_var(&env, msh, msh->argv[i]) == -1)
			error_export(msh->argv[i], &err_flag);
	}
	return (err_flag);
}
