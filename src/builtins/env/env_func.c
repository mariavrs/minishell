/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 09:11:58 by ede-smet          #+#    #+#             */
/*   Updated: 2023/02/01 09:11:58 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/mini_fun.h"

static char	*get_full_var(char *var, char *value)
{
	char	*full_var;
	int		size;
	int		i;

	i = -1;
	size = ft_strlen(var) + ft_strlen(value) + 1;
	full_var = ft_malloc_str(size + 1);
	if (!full_var)
		return (NULL);
	while (full_var && i < size - 1)
	{
		while (*var)
			full_var[++i] = *var++;
		full_var[++i] = '=';
		while (*value)
			full_var[++i] = *value++;
	}
	full_var[i + 1] = '\0';
	return (full_var);
}

int	env_edit(t_msh *msh, char *var, char *value, int flag)
{
	t_env	env;

	env.full_var = get_full_var(var, value);
	if (!env.full_var)
		return (1);
	env.name = ft_strdup(var);
	if (!env.name)
		return (ft_free_str(&env.full_var), 1);
	env.name_ln = ft_strlen(env.name);
	env.i = find_in_envp(&env, msh);
	if (flag == ENV_EXP)
		env_replace(env, msh->envp);
	else if (flag == ENV_LCL)
		env_replace(env, msh->envp_lcl);
	return (ft_free_str(&env.name), 0);
}

int	env_get(char **value, char *name, t_msh *msh)
{
	t_env	env;

	*value = NULL;
	env.name = name;
	env.name_ln = ft_strlen(name);
	env.i = find_in_envp(&env, msh);
	if (env.i == -1)
		return (0);
	if (env.src == ENV_EXP)
		env.value = msh->envp[env.i] + env.name_ln;
	else
		env.value = msh->envp_lcl[env.i] + env.name_ln;
	if (env.value[0] == '\0' || (env.value[0] == '=' && env.value[1] == '\0'))
		return (0);
	else
		env.value++;
	*value = ft_strdup(env.value);
	if (!(*value))
		return (1);
	return (0);
}

int	env_del(t_msh *msh, char *var)
{
	t_env	env;

	env.name = var;
	env.name_ln = ft_strlen(var);
	env.i = find_in_envp(&env, msh);
	if (env.src == ENV_EXP)
		return (del(msh, env, msh->envp));
	else if (env.src == ENV_LCL)
		return (del(msh, env, msh->envp_lcl));
	return (0);
}
