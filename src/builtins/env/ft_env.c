/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/02 22:20:08 by ede-smet         ###   ########.fr       */
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

int	ft_parent_env_cpy(char ***env, char **envp)
{
	int		nb_env;
	int		i;

	i = -1;
	nb_env = ft_count_elem(envp);
	(*env) = NULL;
	(*env) = malloc((nb_env + 1) * sizeof(char *));
	if (!(*env))
		return (ft_putstr_fd("minishell: malloc error\n", 2), 1);
	while (envp[++i])
	{
		(*env)[i] = ft_strdup(envp[i]);
		if (!(*env)[i])
			return (ft_free_dbl_str(env),
				ft_putstr_fd("minishell: malloc error\n", 2), 1);
	}
	(*env)[i] = NULL;
	return (0);
}

int	ft_env(t_msh msh, int mode)
{
	int		i;

	i = -1;
	if (mode == 1)
		while (msh.envp[++i])
			ft_putendl_fd(msh.envp[i], 1);
	else
	{
		while (msh.envp[++i])
			if (ft_strncmp(msh.envp[i] + pos_sep(msh.envp[i]), "\"\"\0", 3)
				&& pos_sep(msh.envp[i]))
				ft_putendl_fd(msh.envp[i], 1);
	}
	return (0);
}
