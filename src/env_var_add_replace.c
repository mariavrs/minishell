/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_add_replace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:17:30 by mvorslov          #+#    #+#             */
/*   Updated: 2023/03/16 16:59:18 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

int	env_lcl_replace(t_env env, char **envp)
{
	ft_free_str(&envp[env.i]);
	envp[env.i] = env.full_var;
	return (0);
}

int	env_lcl_add(t_env env, t_msh *msh, char **envp, int env_flag)
{
	char	**envp_tmp;

	env.i = 0;
	while (msh->envp[env.i])
		env.i++;
	envp_tmp = malloc(sizeof(char *) * (env.i + 2));
	if (!envp_tmp)
		return (ft_putstr_fd("minishell: malloc error\n", 2), 1);
	env.i = -1;
	while (envp[++env.i])
		envp_tmp[env.i] = envp[env.i];
	free(envp);
	envp = NULL;
	envp = envp_tmp;
	envp[env.i] = NULL;
	envp[env.i + 1] = NULL;
	if (!env_flag)
		msh->envp_lcl = envp;
	else
		msh->envp = envp;
	return (env_lcl_replace(env, envp));
}

int	find_in_envp(t_env env, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (!ft_strncmp(env.full_var, envp[i], env.name_ln)
			&& ((env.full_var[env.name_ln] == '=')
				|| (env.full_var[env.name_ln] == '\0'))
			&& ((envp[i][env.name_ln] == '=')
			|| (envp[i][env.name_ln] == '\0')))
			return (i);
	return (-1);
}
