/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:23:09 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/04 21:37:30 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/mini_fun.h"

int	env_not_exist(t_msh *msh, char *var, int flag)
{
	t_env	env;

	env.name = var;
	env.name_ln = ft_strlen(var);
	if (find_in_envp(&env, msh) == -1)
		return (1);
	if (env.src == flag)
		return (0);
	return (1);
}

int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int	pos_sep(char *str)
{
	int	i;

	i = -1;
	while (++i < (int)ft_strlen(str))
		if (str[i] == '=')
			return (i + 1);
	return (0);
}

int	del(t_msh *msh, t_env env, char **envp)
{
	char	**envp_new;
	int		size;

	size = 0;
	while (envp[size])
		size++;
	envp_new = NULL;
	envp_new = malloc(sizeof(char *) * size);
	if (!envp_new)
		return (ft_putstr_fd("minishell: malloc error\n", 2), 1);
	envp_new[size - 1] = NULL;
	size = -1;
	while (envp[++size] && size != env.i)
		envp_new[size] = envp[size];
	while (envp[++size])
		envp_new[size - 1] = envp[size];
	ft_free_str(&envp[env.i]);
	free(envp);
	if (env.src == ENV_EXP)
		msh->envp = envp_new;
	else if (env.src == ENV_LCL)
		msh->envp_lcl = envp_new;
	return (0);
}

char	*get_e_val(char *full_name)
{
	char	*e_val;

	if (pos_sep(full_name) > 0)
	{
		e_val = ft_strdup(full_name + pos_sep(full_name));
		if (!e_val)
			return (ft_putstr_fd("minishell: malloc error\n", 2), NULL);
	}
	else
	{
		e_val = ft_strdup("");
		if (!e_val)
			return (ft_putstr_fd("minishell: malloc error\n", 2), NULL);
	}
	return (e_val);
}
