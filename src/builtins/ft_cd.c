/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/03/19 14:41:18 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

int	ft_cd(char **input, t_msh *msh)
{
	char	current_dir[PATH_MAX];
	char	*dir;
	char	*home;

	if (!input)
		return (1);
	getcwd(current_dir, PATH_MAX);
	home = env_get(msh->envp, "HOME");
	if (!home && !input[1])
		return (write(2, "cd: HOME not set\n", 17), 1);
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
		return (perror("cd"), ft_free_str(&home), 1);
}
