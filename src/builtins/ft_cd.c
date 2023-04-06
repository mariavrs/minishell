/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/02 13:37:38 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

char	*current_pwd(t_msh *msh)
{
	if (!env_not_exist(msh, msh->envp, "PWD"))
		return (env_get(msh, msh->envp, "PWD"));
	else
		return (env_get(msh, msh->envp_lcl, "PWD"));
}

int	check_if_pwd_equal_envp(t_msh *msh, char *var)
{
	t_env	env;

	env.name = var;
	env.name_ln = ft_strlen(var);
	env.i = find_in_envp(&env, msh);
	if (msh->envp[env.i][env.name_ln] == '=')
		return (0);
	return (1);
}

int	ft_cd(char **input, t_msh *msh)
{
	char	current_dir[PATH_MAX];
	char	*dir;
	char	*home;
	char	*error;

	home = env_get(msh, msh->envp, "HOME");
	if (cd_error(input, home))
		return (ft_free_str(&home), 1);
	dir = home;
	if (input[1])
		dir = input[1];
	if (chdir(dir) == 0)
	{
		getcwd(current_dir, PATH_MAX);
		if (fill_env(msh, current_dir))
			return (ft_free_str(&home), 1);
		return (ft_free_str(&home), 0);
	}
	error = ft_strjoin("minishell: cd: ", input[1]);
	if (!error)
		return (malloc_error(msh),
			ft_free_str(&home), 1);
	return (perror(error), ft_free_str(&error), ft_free_str(&home), 1);
}
