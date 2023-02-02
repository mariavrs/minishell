/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/02/02 13:29:26 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

int	ft_count_elem(char **envp)
{
	int	i;

	i = 0;
	while (*envp++)
		i++;
	return (i);
}

int	ft_parent_env_cpy(char ***env, char **envp)
{
	int		nb_env;
	int		i;

	i = -1;
	nb_env = ft_count_elem(envp);
	(*env) = malloc((nb_env + 1) * sizeof(char *));
	if (!(*env))
		return (1);
	while (envp[++i])
	{
		(*env)[i] = NULL;
		(*env)[i] = malloc ((ft_strlen(envp[i]) + 1) * sizeof(char));
		if (!(*env)[i])
			return (1);
		ft_strlcpy((*env)[i], envp[i], ft_strlen(envp[i]) + 1);
	}
	(*env)[i++] = NULL;
	return (0);
}

int	ft_env(char **env)
{
	while (*env)
		printf("%s\n", *env++);
	return (0);
}
