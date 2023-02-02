/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/02/02 13:33:46 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

int	ft_cd(char **input, char ***env)
{
	char	tmp_dir[1000];
	char	*home;

	getcwd(tmp_dir, 1000);
	env_edit(env, "OLDPWD", tmp_dir);
	home = env_get(*env, "HOME");
	if ((!input || !input[1]) && chdir(home) == 0)
		return (env_edit(env, "PWD", home), free(home), 0);
	if (chdir(input[1]) == 0)
	{
		getcwd(tmp_dir, 1000);
		env_edit(env, "PWD", tmp_dir);
		return (free(home), 0);
	}
	return (free(home), 1);
}
