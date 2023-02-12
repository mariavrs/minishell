/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/02/12 19:58:53 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

int	ft_cd(char **input, char ***env)
{
	char	current_dir[PATH_MAX];
	char	*home;

	getcwd(current_dir, PATH_MAX);
	home = env_get(*env, "HOME");
	if (!home && !input[1])
		return (free(home), write(2, "cd: HOME not set\n", 17), 1);
	if (!input[1])
		input[1] = home;
	env_edit(env, "OLDPWD", current_dir);
	if (chdir(input[1]) == 0)
	{
		getcwd(current_dir, PATH_MAX);
		env_edit(env, "PWD", current_dir);
		return (free(home), 0);
	}
	else
		return (perror("cd"), free(home), 1);
}
