/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/02/01 13:10:23 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

static int	ft_count_elem(char **envp)
{
	int	i;

	i = 0;
	while (*envp++)
		i++;
	return (i);
}

void	ft_parent_env_cpy(t_env *env, char **envp)
{
	int		nb_env;
	int		i;

	i = -1;
	nb_env = ft_count_elem(envp);
	env->env_cp = malloc((nb_env + 1) * sizeof(char *));
	if (!env)
		return ;
	while (envp[++i])
	{
		env->env_cp[i] = NULL;
		env->env_cp[i] = malloc ((ft_strlen(envp[i]) + 1) * sizeof(char));
		if (!env->env_cp[i])
			return ;
		ft_strlcpy(env->env_cp[i], envp[i], ft_strlen(envp[i]) + 1);
	}
	env->env_cp[i++] = NULL;
}

int	ft_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
	return (0);
}
