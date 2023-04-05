/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/05 23:49:08 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

char	*get_value(t_msh *msh, char *var)
{
	char	*value;

	if (env_get(&value, var, msh))
		return (NULL);
	if (!value)
	{
		value = ft_strdup("\0");
		if (!value)
			return (ft_putstr_fd("minishell: malloc error\n", 2), NULL);
	}
	return (value);
}

int	check_if_pwd_equal_envp(t_msh *msh, char *var)
{
	t_env	env;

	env.name = var;
	env.name_ln = ft_strlen(var);
	env.i = find_in_envp(&env, msh);
	if (env.src == ENV_EXP)
		if (msh->envp[env.i] && msh->envp[env.i][env.name_ln] == '=')
			return (1);
	if (env.src == ENV_LCL)
		if (msh->envp_lcl[env.i] && msh->envp_lcl[env.i][env.name_ln] == '=')
			return (1);
	return (0);
}

int	fill_dir(t_msh *msh, char **dir, char **home)
{
	if (msh->argv[1])
		*dir = msh->argv[1];
	else
		*dir = *home;
	return (0);
}

int	ft_cd(t_msh *msh)
{
	char	current_dir[PATH_MAX];
	char	*dir;
	char	*home;
	char	*error;

	home = get_value(msh, "HOME");
	if (error_cd(msh, home))
		return (ft_free_str(&home), 1);
	if (home[0] == '\0' && !msh->argv[1])
		return (ft_free_str(&home), 0);
	if (fill_dir(msh, &dir, &home))
		return (1);
	if (chdir(dir) == 0)
	{
		if (!getcwd(current_dir, PATH_MAX) || fill_env(msh, current_dir))
			return (ft_putstr_fd("minishell: malloc error\n", 2),
				ft_free_str(&home), 1);
		return (ft_free_str(&home), 0);
	}
	error = ft_strjoin("minishell: cd: ", dir);
	if (!error)
		return (ft_putstr_fd("minishell: malloc error\n", 2),
			ft_free_str(&home), 1);
	return (perror(error), ft_free_str(&error), ft_free_str(&home), 1);
}
