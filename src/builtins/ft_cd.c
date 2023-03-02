/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/03/02 17:51:22 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

int	ft_cd(char **input, t_msh *msh)
{
	char	current_dir[PATH_MAX];
	char	*home;
	char	*dir;

	if (!input)
		return (1);
	getcwd(current_dir, PATH_MAX);
	home = env_get(msh->envp, "HOME");
	if (!home && !input[1])
		return (write(2, "cd: HOME not set\n", 17), 1);
	if (home && !input[1])
		dir = home;
	else
		dir = input[1];
	env_edit(&msh->envp, "OLDPWD", current_dir);
	if (chdir(dir) == 0)
	{
		getcwd(current_dir, PATH_MAX);
		env_edit(&msh->envp, "PWD", current_dir);
		if (home)
			ft_free_str(&home);
		return (0);
	}
	else
	{
		if (home)
			ft_free_str(&home);
		return (perror("cd"), 1);
	}
}
