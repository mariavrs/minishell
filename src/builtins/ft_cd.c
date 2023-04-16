/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/16 19:22:35 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

typedef struct s_ft_cd
{
	char	current_dir[PATH_MAX];
	char	*dir;
	char	*home;
	char	*error;
	int		return_err;
}	t_ft_cd;

char	*cd_get_value(t_msh *msh, char *var)
{
	char	*value;

	value = NULL;
	if (env_get(&value, var, msh))
		return (NULL);
	if (!value)
	{
		value = ft_strdup("\0");
		if (!value)
			return (malloc_error(), NULL);
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

static int	fill_dir(char **argv, char **dir, char **home)
{
	if (argv[1])
		*dir = argv[1];
	else
		*dir = *home;
	return (0);
}

static int	get_current_pwd(t_ft_cd *cd, t_msh *msh, char *argv)
{
	if (!getcwd(cd->current_dir, PATH_MAX))
	{
		ft_putendl_fd("cd: error retrieving current directory: getcwd: \
cannot access parent directories: No such file or directory", 2);
		if (!ft_strncmp(argv, "..", 3) || !ft_strncmp(argv, "../", 4))
		{
			if (build_pwd(cd->current_dir, msh, argv))
				return (ft_free_str(&cd->home),
					ft_exit_error(0, NULL, msh, ERR_MALLOC), ERR_MALLOC);
			return (0);
		}
		else
			return (1);
	}
	return (0);
}

int	ft_cd(t_msh *msh, char **argv)
{
	t_ft_cd	cd;

	cd.home = cd_get_value(msh, "HOME");
	if (!cd.home)
		return (ft_exit_error(0, NULL, msh, ERR_MALLOC), ERR_MALLOC);
	if (error_cd(msh, argv, cd.home))
		return (ft_free_str(&cd.home), 1);
	if (cd.home[0] == '\0' && !argv[1])
		return (ft_free_str(&cd.home), 0);
	if (fill_dir(argv, &cd.dir, &cd.home))
		return (1);
	if (chdir(cd.dir) == 0)
	{
		cd.return_err = get_current_pwd(&cd, msh, argv[1]);
		if (cd.return_err)
			return (cd.return_err);
		if (cd_fill_env(msh, cd.current_dir, &cd.home))
			return (ft_exit_error(0, NULL, msh, ERR_MALLOC), ERR_MALLOC);
		return (0);
	}
	cd.error = ft_strjoin("minishell: cd: ", cd.dir);
	if (!cd.error)
		return (malloc_error(), ft_free_str(&cd.home), ft_exit_error(0, NULL,
				msh, ERR_MALLOC), ERR_MALLOC);
	return (perror(cd.error), ft_free_str(&cd.error), ft_free_str(&cd.home), 1);
}
