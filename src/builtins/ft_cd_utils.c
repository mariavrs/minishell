/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 13:46:17 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/06 00:05:30 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

static int	fill_env_pwd(t_msh *msh, char *path)
{
	if (env_not_exist(msh, "PWD", ENV_EXP))
		return (env_edit(msh, "PWD", path, ENV_LCL));
	else
		return (env_edit(msh, "PWD", path, ENV_EXP));
}

static int	unset_case(t_msh *msh)
{
	t_env	env;

	if (env_not_exist(msh, "PWD", ENV_EXP)
		&& env_not_exist(msh, "PWD", ENV_LCL))
	{
		env.full_var = ft_strdup("PWD");
		if (!env.full_var)
			return (1);
		if (env_add(env, msh, msh->envp_lcl, ENV_LCL))
			return (1);
	}
	if (env_not_exist(msh, "OLDPWD", ENV_EXP)
		&& env_not_exist(msh, "OLDPWD", ENV_LCL))
	{
		env.full_var = ft_strdup("OLDPWD");
		if (!env.full_var)
			return (1);
		if (env_add(env, msh, msh->envp_lcl, ENV_LCL))
			return (1);
	}
	return (0);
}

static int	if_pwd_is_empty_case(t_msh *msh)
{
	t_env	env;

	if (env_not_exist(msh, "OLDPWD", ENV_EXP))
	{
		env.full_var = ft_strdup("OLDPWD");
		if (!env.full_var)
			return (1);
		env.name = "OLDPWD";
		env.name_ln = ft_strlen(env.name);
		env.i = find_in_envp(&env, msh);
		env_replace(env, msh->envp_lcl);
	}
	else
	{
		env.full_var = ft_strdup("OLDPWD");
		if (!env.full_var)
			return (1);
		env.name = "OLDPWD";
		env.name_ln = ft_strlen(env.name);
		env.i = find_in_envp(&env, msh);
		env_replace(env, msh->envp);
	}
	return (0);
}

static int	set_env(t_msh *msh, t_env *env, char *name, char *full_var_str)
{
	if (!full_var_str)
		return (1);
	env->name = name;
	env->name_ln = ft_strlen(env->name);
	env->full_var = full_var_str;
	env->i = find_in_envp(env, msh);
	env->dest = env->src;
	put_env_var(env, msh);
	return (0);
}

int	fill_env(t_msh *msh, char *path)
{
	t_env	env;

	if (unset_case(msh))
		return (1);
	env.value = get_value(msh, "PWD");
	if (!env.value)
		return (1);
	if (!ft_strlen(env.value) && !check_if_pwd_equal_envp(msh, "PWD"))
	{
		if (if_pwd_is_empty_case(msh))
			return (ft_free_str(&env.value), 1);
		if (fill_env_pwd(msh, path))
			return (ft_free_str(&env.value), 1);
	}
	else
	{
		if (set_env(msh, &env, "OLDPWD", ft_strjoin("OLDPWD=", env.value)))
			return (1);
		if (set_env(msh, &env, "PWD", ft_strjoin("PWD=", path)))
			return (1);
	}
	return (ft_free_str(&env.value), 0);
}
