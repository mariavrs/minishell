/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 13:46:17 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/02 13:36:03 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

static int	fill_env_pwd(t_msh *msh, char *path)
{
	if (!env_not_exist(msh->envp, "PWD"))
		return (env_edit(msh, "PWD", path, ENV_EXP));
	else
		return (env_edit(msh, "PWD", path, ENV_LCL));
}

static int	unset_case(t_msh *msh)
{
	t_env	env;

	if (env_not_exist(msh->envp, "PWD"))
	{
		env.full_var = ft_strdup("PWD");
		if (!env.full_var)
			return (ft_putstr_fd("minishell: malloc error \n", 2), 1);
		if (env_add(env, msh, msh->envp_lcl, ENV_LCL))
			return (1);
	}
	if (env_not_exist(msh->envp, "OLDPWD"))
	{
		env.full_var = ft_strdup("OLDPWD");
		if (!env.full_var)
			return (ft_putstr_fd("minishell: malloc error \n", 2), 1);
		if (env_add(env, msh, msh->envp_lcl, ENV_LCL))
			return (1);
	}
	return (0);
}

static int	if_pwd_is_empty_case(t_msh *msh)
{
	t_env	env;

	if (!env_not_exist(msh->envp, "OLDPWD"))
	{
		if (env_del(&msh->envp, "OLDPWD"))
			return (1);
		env.full_var = ft_strdup("OLDPWD");
		if (!env.full_var)
			return (ft_putstr_fd("minishell: malloc error \n", 2), 1);
		if (env_add(env, msh, msh->envp, ENV_EXP))
			return (1);
	}
	else
	{
		if (env_del(&msh->envp_lcl, "OLDPWD"))
			return (1);
		env.full_var = ft_strdup("OLDPWD");
		if (!env.full_var)
			return (ft_putstr_fd("minishell: malloc error \n", 2), 1);
		if (env_add(env, msh, msh->envp_lcl, ENV_LCL))
			return (1);
	}
	return (0);
}

static int	fill_right_env(t_msh *msh, char *c_pwd, char *path, int flag)
{
	if (flag == ENV_EXP)
	{
		if (env_edit(msh, "OLDPWD", c_pwd, ENV_EXP))
			return (1);
		if (fill_env_pwd(msh, path))
			return (1);
	}
	else if (flag == ENV_LCL)
	{
		if (env_edit(msh, "OLDPWD", c_pwd, ENV_LCL))
			return (1);
		if (fill_env_pwd(msh, path))
			return (1);
	}
	return (0);
}

int	fill_env(t_msh *msh, char *path)
{
	char	*c_pwd;

	if (unset_case(msh))
		return (1);
	c_pwd = current_pwd(msh);
	if (!ft_strlen(c_pwd) && check_if_pwd_equal_envp(msh, "PWD"))
	{
		if (if_pwd_is_empty_case(msh))
			return (ft_free_str(&c_pwd), 1);
		if (fill_env_pwd(msh, path))
			return (ft_free_str(&c_pwd), 1);
	}
	else if (!env_not_exist(msh->envp, "OLDPWD"))
	{
		if (fill_right_env(msh, c_pwd, path, ENV_EXP))
			return (ft_free_str(&c_pwd), 1);
	}
	else
	{
		if (fill_right_env(msh, c_pwd, path, ENV_LCL))
			return (ft_free_str(&c_pwd), 1);
	}
	return (ft_free_str(&c_pwd), 0);
}
