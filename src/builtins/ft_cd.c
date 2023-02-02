/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/02/01 14:18:19 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

int	ft_cd(char **input, t_env *env)
{
	char	tmp_dir[1000];

	if (!input || !input[1])
		return (1);
	getcwd(tmp_dir, 1000);
	env_edit(env, "OLDPWD", tmp_dir);
	if (chdir(input[1]) == 0)
	{
		getcwd(tmp_dir, 1000);
		env_edit(env, "PWD", tmp_dir);
		return (0);
	}
	return (1);
}
