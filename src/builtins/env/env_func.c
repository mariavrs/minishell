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

void	ft_fill_env(char *env, char *var, char *value)
{
	int	i;
	int	k;

	i = -1;
	k = -1;
	while (++k < (int)ft_strlen(var))
		env[++i] = var[k];
	env[++i] = '=';
	k = -1;
	while (++k < (int)ft_strlen(value))
		env[++i] = value[k];
	env[++i] = '\0';
}

void	free_table(char **table)
{
	int	i;

	i = 0;
	if (!table)
		return ;
	while (table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
}

int	env_edit(t_env *env, char *var, char *value)
{
	int		i;
	char	**tmp;

	i = -1;
	tmp = NULL;
	while (env->env_cp[++i])
	{
		tmp = ft_split(env->env_cp[i], '=');
		if (ft_strncmp(tmp[0], var, ft_strlen(var) + 1) == 0)
		{
			free(env->env_cp[i]);
			env->env_cp[i] = NULL;
			env->env_cp[i] = malloc((ft_strlen(tmp[0]) + ft_strlen(value) + 2)
					* sizeof(char));
			if (!env->env_cp[i])
				return (free_table(tmp), 1);
			ft_fill_env(env->env_cp[i], tmp[0], value);
		}
		free_table(tmp);
	}
	return (0);
}

char	*env_get(char **env, char *var)
{
	char	**tmp;
	char	*value;
	int		i;

	i = -1;
	while (env[++i])
	{
		tmp = ft_split(env[i], '=');
		if (ft_strncmp(tmp[0], var, ft_strlen(var) + 1) == 0)
		{
			value = NULL;
			value = malloc((ft_strlen(tmp[1]) + 1)
					* sizeof(char));
			if (!value)
				return (free_table(tmp), NULL);
			ft_strlcpy(value, tmp[1], ft_strlen(tmp[1]) + 1);
		}
		free_table(tmp);
	}
	return (value);
}
/* 
int	env_add(char **env, char *var, char *value)
{
	return (0);
}

int	env_del(char **env, char *var, char *value)
{
	return (0);
} */
