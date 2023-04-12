/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_prep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 22:28:07 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/12 20:02:39 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

static int	ft_parent_env_cpy(char ***env, char **envp)
{
	int		nb_env;
	int		i;

	i = -1;
	nb_env = 0;
	while (envp[nb_env])
		nb_env++;
	(*env) = NULL;
	(*env) = ft_malloc_dbl_str(nb_env + 1);
	if (!(*env))
		return (1);
	while (envp[++i])
	{
		(*env)[i] = ft_strdup(envp[i]);
		if (!(*env)[i])
			return (ft_free_dbl_str(env),
				malloc_error(), 1);
	}
	(*env)[i++] = NULL;
	return (0);
}

int	msh_prep(t_msh *msh, char **envp)
{
	if (ft_parent_env_cpy(&(msh->envp), envp))
		return (1);
	msh->envp_lcl = NULL;
	msh->envp_lcl = ft_malloc_dbl_str(1);
	if (!msh->envp_lcl)
		return (ft_free_dbl_str(&msh->envp), 1);
	msh->ex_sline = NULL;
	msh->cmd_list = NULL;
	msh->prompt = NULL;
	msh->pipe_flag = 0;
	return (0);
}
