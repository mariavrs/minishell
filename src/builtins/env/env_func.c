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
	char	**t_e;
	char	**t_s;
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
		if (!tmp)
			return (1);
		if (ft_strncmp(tmp[0], var, ft_strlen(var) + 1) == 0)
		{
			free((*env)[i]);
			(*env)[i] = NULL;
			(*env)[i] = malloc((ft_strlen(tmp[0]) + ft_strlen(value) + 2)
					* sizeof(char));
			if (!(*env)[i])
				return (ft_free_dbl_str(&tmp), 1);
			ft_fill_env((*env)[i], tmp[0], value);
		}
		ft_free_dbl_str(&tmp);
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
		if (!tmp)
			return (NULL);
		if (ft_strncmp(tmp[0], var, ft_strlen(var) + 1) == 0)
		{
			value = NULL;
			value = malloc((ft_strlen(tmp[1]) + 1)
					* sizeof(char));
			if (!value)
				return (ft_free_dbl_str(&tmp), NULL);
			if (tmp[1])
				ft_strlcpy(value, env[i] + pos_sep(env[i]),
					ft_strlen(env[i] + pos_sep(env[i])) + 1);
		}
		ft_free_dbl_str(&tmp);
	}
	return (value);
}

int	env_add(char ***env, char *value)
{
	char	**env_tmp;
	int		i;

	i = -1;
	if (ft_parent_env_cpy(&env_tmp, *env))
		return (1);
	ft_free_dbl_str(env);
	*env = malloc ((ft_count_elem(env_tmp) + 2) * sizeof(char *));
	if (!(*env))
		return (ft_free_dbl_str(&env_tmp), 1);
	while (env_tmp[++i])
	{
		(*env)[i] = malloc ((ft_strlen(env_tmp[i]) + 1) * sizeof(char));
		if (!(*env))
			return (ft_free_dbl_str(&env_tmp), 1);
		ft_strlcpy((*env)[i], env_tmp[i], ft_strlen(env_tmp[i]) + 1);
	}
	(*env)[i] = malloc ((ft_strlen(value) + 1) * sizeof(char));
	if (!(*env))
		return (ft_free_dbl_str(&env_tmp), 1);
	ft_strlcpy((*env)[i], value, ft_strlen(value) + 1);
	(*env)[++i] = NULL;
	return (ft_free_dbl_str(&env_tmp), 0);
}

int	env_del(char ***env, char *var)
{
	t_del	d;

	d.k = 0;
	d.i = -1;
	if (env_exist(*env, var) || ft_parent_env_cpy(&d.t_e, *env))
		return (1);
	ft_free_dbl_str(env);
	*env = malloc (ft_count_elem(d.t_e) * sizeof(char *));
	if (!(*env))
		return (ft_free_dbl_str(&d.t_e), 1);
	while (d.t_e[++d.i])
	{
		d.t_s = ft_split(d.t_e[d.i], '=');
		if (!d.t_s)
			return (1);
		if (ft_strncmp(d.t_s[0], var, ft_strlen(var) + 1) != 0)
		{
			(*env)[d.k] = malloc ((ft_strlen(d.t_e[d.i]) + 1) * sizeof(char));
			if (!(*env))
				return (ft_free_dbl_str(&d.t_e), 1);
			ft_strlcpy((*env)[d.k++], d.t_e[d.i], ft_strlen(d.t_e[d.i]) + 1);
		}
		ft_free_dbl_str(&d.t_s);
	}
	return ((*env)[d.k] = NULL, ft_free_dbl_str(&d.t_e), 0);
}
