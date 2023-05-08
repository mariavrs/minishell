/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/07 16:58:49 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

int	if_not_exist(t_msh *msh, char *var, int src)
{
	t_env	env;

	env.name = var;
	env.name_ln = ft_strlen(var);
	if (find_in_envp(&env, msh) == -1)
		return (1);
	if (env.src == src)
		return (0);
	return (1);
}

int	dbl_str_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int	env_val_start_pos(char *str)
{
	int	i;

	i = -1;
	while (++i < (int)ft_strlen(str))
		if (str[i] == '=')
			return (i + 1);
	return (0);
}

int	ft_env(t_msh *msh, char **argv, int mode)
{
	int		i;

	(void)argv;
	i = -1;
	if (mode == 1)
		while (msh->envp[++i])
			ft_putendl_fd(msh->envp[i], 1);
	else
	{
		while (msh->envp[++i])
			if (ft_strncmp(msh->envp[i] + env_val_start_pos(msh->envp[i]),
					"\"\"\0", 3)
				&& env_val_start_pos(msh->envp[i]))
				ft_putendl_fd(msh->envp[i], 1);
	}
	return (0);
}
