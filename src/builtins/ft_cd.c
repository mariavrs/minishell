/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/03/28 21:53:35 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

static int	cd_error(char **input, char *home)
{
	if (!input)
		return (1);
	if (env_size(input) > 2)
		return (write(2, "cd: too many arguments\n", 23), 1);
	if (!home && !input[1])
		return (write(2, "cd: HOME not set\n", 17), 1);
	return (0);
}

int	ft_cd(char **input, t_msh *msh)
{
	char	current_dir[PATH_MAX];
	char	*dir;
	char	*home;
	char	*error;

	home = env_get(msh->envp, "HOME");
	if (getcwd(current_dir, PATH_MAX) && cd_error(input, home))
		return (ft_free_str(&home), 1);
	if (input[1])
		dir = input[1];
	else
		dir = home;
	if (!env_edit(&msh->envp, "OLDPWD", current_dir) && chdir(dir) == 0)
	{
		getcwd(current_dir, PATH_MAX);
		env_edit(&msh->envp, "PWD", current_dir);
		return (ft_free_str(&home), 0);
	}
	else if (env_edit(&msh->envp, "OLDPWD", current_dir))
		return (ft_putstr_fd("minishell: malloc error\n", 2), 1);
	else
	{
		error = ft_strjoin("cd: ", input[1]);
		return (perror(error), ft_free_str(&error), ft_free_str(&home), 1);
	}
}
