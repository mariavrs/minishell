/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/16 19:43:51 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

int	build_pwd(char *current_dir, t_msh *msh, char *argv)
{
	char	*path;

	ft_bzero(current_dir, PATH_MAX);
	if (env_get(&path, "PWD", msh))
		return (1);
	if (!path)
		return (0);
	ft_strlcpy(current_dir, path, ft_strlen(path) + 1);
	current_dir[ft_strlen(path)] = '/';
	ft_strlcpy(current_dir + ft_strlen(path) + 1, argv, ft_strlen(argv) + 1);
	return (ft_free_str(&path), 0);
}

int	ft_pwd(t_msh *msh)
{
	char	path[PATH_MAX];
	char	*pwd;

	if (!getcwd(path, PATH_MAX))
	{
		env_get(&pwd, "PWD", msh);
		if (!pwd)
			return (ft_putendl_fd("pwd: cannot access current directory",
					2), 1);
		else
		{
			ft_putendl_fd(pwd, 1);
			ft_free_str(&pwd);
		}
	}
	else
		ft_putendl_fd(path, 1);
	return (0);
}
