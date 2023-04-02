/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_declare_put_var.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 20:09:29 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/02 13:36:07 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

int	env_replace(t_env env, char **envp)
{
	ft_free_str(&envp[env.i]);
	envp[env.i] = env.full_var;
	return (0);
}

int	env_add(t_env env, t_msh *msh, char **envp, int env_flag)
{
	char	**envp_tmp;

	env.i = 0;
	while (envp[env.i])
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
	if (env_flag == ENV_LCL)
		msh->envp_lcl = envp;
	else
		msh->envp = envp;
	return (env_replace(env, envp));
}

int	put_env_var(t_env *env, t_msh *msh)
{
	if (env->dest == ENV_LCL && env->src == env->dest)
		return (env_replace(*env, msh->envp_lcl));
	else if (env->dest == ENV_EXP && env->src == env->dest)
		return (env_replace(*env, msh->envp));
	else if (env->dest == ENV_LCL && env->src != env->dest)
		return (env_add(*env, msh, msh->envp_lcl, ENV_LCL));
	else if (env->dest == ENV_EXP && env->src != env->dest)
		return (env_add(*env, msh, msh->envp, ENV_EXP));
	return (0);
}
