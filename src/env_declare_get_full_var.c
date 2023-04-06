/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_declare_get_full_var.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:17:30 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/02 18:28:24 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

int	get_env_mod(char c)
{
	if (c == '=')
		return (ENV_REPLC);
	else if (c == '+')
		return (ENV_APPEND);
	else
		return (ENV_EXPND);
}

static void	full_var_join(t_env *env, t_msh *msh)
{
	int	len_if_in_envp;

	if (env->mod == ENV_REPLC)
	{
		ft_strlcpy(env->full_var, env->name, env->name_ln + 1);
		env->full_var[env->name_ln] = '=';
		ft_strlcpy(&env->full_var[env->name_ln + 1],
			env->value, env->value_ln + 1);
	}
	else if (env->mod == ENV_APPEND && env->src == ENV_LCL)
	{
		len_if_in_envp = ft_strlen(msh->envp_lcl[env->i]);
		ft_strlcpy(env->full_var, msh->envp_lcl[env->i], len_if_in_envp + 1);
		ft_strlcpy(&env->full_var[len_if_in_envp],
			env->value, env->value_ln + 1);
	}
	else if (env->mod == ENV_APPEND && env->src == ENV_EXP)
	{
		len_if_in_envp = ft_strlen(msh->envp[env->i]);
		ft_strlcpy(env->full_var, msh->envp[env->i], len_if_in_envp + 1);
		if (!msh->envp[env->name_ln])
			env->full_var[len_if_in_envp++] = '=';
		ft_strlcpy(&env->full_var[len_if_in_envp],
			env->value, env->value_ln + 1);
	}
}

int	find_in_envp(t_env *env, t_msh *msh)
{
	int	i;

	i = -1;
	while (msh->envp_lcl[++i])
		if (!ft_strncmp(env->name, msh->envp_lcl[i], env->name_ln)
			&& ((env->name[env->name_ln] == '=')
				|| (env->name[env->name_ln] == '\0')
				|| (env->name[env->name_ln] == '+'))
			&& ((msh->envp_lcl[i][env->name_ln] == '=')
			|| (msh->envp_lcl[i][env->name_ln] == '\0')))
			return (env->src = ENV_LCL, i);
	i = -1;
	while (msh->envp[++i])
		if (!ft_strncmp(env->name, msh->envp[i], env->name_ln)
			&& ((env->name[env->name_ln] == '=')
				|| (env->name[env->name_ln] == '\0')
				|| (env->name[env->name_ln] == '+'))
			&& ((msh->envp[i][env->name_ln] == '=')
			|| (msh->envp[i][env->name_ln] == '\0')))
			return (env->src = ENV_EXP, i);
	return (env->src = -1, -1);
}

int	full_var_if_expand(t_env *env, t_msh *msh)
{
	if (env->src == ENV_LCL)
		env->full_var = ft_strdup(msh->envp_lcl[env->i]);
	else if (env->src == ENV_EXP)
		env->full_var = ft_strdup(msh->envp[env->i]);
	else
		env->full_var = ft_strdup(env->name);
	if (!env->full_var)
		return (malloc_error(msh), 1);
	return (0);
}

int	get_full_var_str(char *line, t_env *env, t_msh *msh)
{
	env->name = line;
	env->i = find_in_envp(env, msh);
	env->value_ln = ft_strlen(env->value);
	if (env->mod == ENV_APPEND && env->i < 0)
		env->mod = ENV_REPLC;
	if (env->mod == ENV_REPLC)
		env->full_var_ln = env->name_ln + env->value_ln + 1;
	else if (env->mod == ENV_APPEND && env->src == ENV_LCL)
		env->full_var_ln = ft_strlen(msh->envp_lcl[env->i]) + env->value_ln;
	else if (env->mod == ENV_APPEND && env->src == ENV_EXP)
		env->full_var_ln = ft_strlen(msh->envp[env->i]) + 1 + env->value_ln;
	if (env->mod == ENV_EXPND)
		return (full_var_if_expand(env, msh));
	env->full_var = ft_malloc_str(msh, env->full_var_ln + 1);
	if (!env->full_var)
		return (1);
	full_var_join(env, msh);
	return (0);
}
