/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/01/30 21:17:01 by ede-smet         ###   ########.fr       */
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

char	**ft_parent_env_cpy(char **envp)
{
	int		nb_env;
	char	**env;
	int		i;

	i = -1;
	env = NULL;
	nb_env = ft_count_elem(envp);
	env = malloc((nb_env + 1) * sizeof(char *));
	if (!env)
		return (NULL);
	while (envp[++i])
	{
		env[i] = malloc ((ft_strlen(envp[i])) * sizeof(char));
		ft_strlcpy(env[i], envp[i], ft_strlen(envp[i]) + 1);
	}
	env[++i] = "\0";
	return (env);
}

int	ft_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
	return (0);
}
