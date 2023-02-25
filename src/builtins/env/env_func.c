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

typedef struct s_del
{
	char	**e_tmp;
	char	**s_tmp;
	int		i;
	int		k;
}	t_del;

int	env_edit(char ***env, char *var, char *value)
{
	int		i;
	char	**tmp;

	i = -1;
	tmp = NULL;
	while ((*env)[++i])
	{
		tmp = ft_split((*env)[i], '=');
		if (ft_strncmp(tmp[0], var, ft_strlen(var) + 1) == 0)
		{
			free((*env)[i]);
			(*env)[i] = NULL;
			(*env)[i] = malloc((ft_strlen(tmp[0]) + ft_strlen(value) + 2)
					* sizeof(char));
			if (!(*env)[i])
				return (free_table(tmp), 1);
			ft_fill_env((*env)[i], tmp[0], value);
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
	value = NULL;
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

int	env_add(char ***env, char *value)
{
	char	**env_tmp;
	int		i;

	i = -1;
	ft_parent_env_cpy(&env_tmp, *env);
	free_table(*env);
	*env = malloc ((ft_count_elem(env_tmp) + 2) * sizeof(char *));
	if (!(*env))
		return (free_table(env_tmp), 1);
	while (env_tmp[++i])
	{
		(*env)[i] = malloc ((ft_strlen(env_tmp[i]) + 1) * sizeof(char));
		if (!(*env))
			return (free_table(env_tmp), 1);
		ft_strlcpy((*env)[i], env_tmp[i], ft_strlen(env_tmp[i]) + 1);
	}
	(*env)[i] = malloc ((ft_strlen(value) + 1) * sizeof(char));
	if (!(*env))
		return (free_table(env_tmp), 1);
	ft_strlcpy((*env)[i], value, ft_strlen(value) + 1);
	(*env)[++i] = NULL;
	return (free_table(env_tmp), 0);
}

int	env_del(char ***env, char *var)
{
	t_del	d;

	d.k = 0;
	d.i = -1;
	if (env_exist(*env, var))
		return (1);
	ft_parent_env_cpy(&d.e_tmp, *env);
	free_table(*env);
	*env = malloc (ft_count_elem(d.e_tmp) * sizeof(char *));
	if (!(*env))
		return (free_table(d.e_tmp), 1);
	while (d.e_tmp[++d.i])
	{
		d.s_tmp = ft_split(d.e_tmp[d.i], '=');
		if (ft_strncmp(d.s_tmp[0], var, ft_strlen(var) + 1) != 0)
		{
			(*env)[d.k] = malloc ((ft_strlen(d.e_tmp[d.i]) + 1) * sizeof(char));
			if (!(*env))
				return (free_table(d.e_tmp), 1);
			ft_strlcpy((*env)[d.k++], d.e_tmp[d.i],
				ft_strlen(d.e_tmp[d.i]) + 1);
		}
		free_table(d.s_tmp);
	}
	return ((*env)[d.k] = NULL, free_table(d.e_tmp), 0);
}
