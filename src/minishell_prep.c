/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_prep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 22:28:07 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/03 02:08:51 by mvorslov         ###   ########.fr       */
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
	(*env) = malloc((nb_env + 1) * sizeof(char *));
	if (!(*env))
		return (malloc_error(), 1);
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
	msh->envp_lcl = malloc(sizeof(char *));
	if (!msh->envp_lcl)
		return (ft_free_dbl_str(&msh->envp), malloc_error(), 1);
	msh->envp_lcl[0] = NULL;
	msh->ex_sline = NULL;
	msh->cmd_list = NULL;
	msh->stdin_default = dup(STDIN_FILENO);
	msh->stdout_default = dup(STDOUT_FILENO);
	msh->malloc_err_parse = 0;
	return (0);
}
