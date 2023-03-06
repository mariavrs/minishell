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
	char	*env_var;

	i = -1;
	while ((*env)[++i])
	{
		env_var = ft_substr((*env)[i], 0, pos_sep((*env)[i]) - 1);
		if (!ft_strncmp(env_var, var, ft_strlen(var) + 1))
		{
			free((*env)[i]);
			(*env)[i] = NULL;
			(*env)[i] = malloc((ft_strlen(env_var) + ft_strlen(value) + 2)
					* sizeof(char));
			if (!(*env)[i])
				return (ft_free_str(&env_var), 1);
			ft_fill_env((*env)[i], env_var, value);
		}
		ft_free_str(&env_var);
	}
	return (0);
}

char	*env_get(char **env, char *var)
{
	char	*e_var;
	char	*e_val;
	int		i;

	i = -1;
	while (env[++i])
	{
		e_var = ft_substr(env[i], 0, pos_sep(env[i]) - 1);
		e_val = ft_strdup(env[i] + pos_sep(env[i]));
		if (!ft_strncmp(e_var, var, ft_strlen(var) + 1))
			return(ft_free_str(&e_var), e_val);
		ft_free_str(&e_var);
		ft_free_str(&e_val);
	}
	return (NULL);
}

int	env_add(char ***env, char *value)
{
	char	**env_tmp;
	char	*val_tmp;
	int		i;

	i = -1;
	if (value[pos_sep(value)] == '\0')
		val_tmp = ft_strjoin(value, "\"\"");
	else
		val_tmp = ft_strdup(value);
	if (ft_parent_env_cpy(&env_tmp, *env))
		return (1);
	ft_free_dbl_str(env);
	*env = malloc ((ft_count_elem(env_tmp) + 2) * sizeof(char *));
	if (!(*env))
		return (ft_free_str(&val_tmp), ft_free_dbl_str(&env_tmp), 1);
	while (env_tmp[++i])
	{
		(*env)[i] = ft_strdup(env_tmp[i]);
		if (!(*env)[i])
			return (ft_free_str(&val_tmp), ft_free_dbl_str(&env_tmp), 1);
	}
	(*env)[i] = ft_strdup(val_tmp);
	if (!(*env)[i])
		return (ft_free_str(&val_tmp), ft_free_dbl_str(&env_tmp), 1);
	(*env)[++i] = NULL;
	return (ft_free_str(&val_tmp), ft_free_dbl_str(&env_tmp), 0);
}

int	env_del(char ***env, char *var)
{
	t_del	d;
	char	*sub;

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
		sub = ft_substr(d.t_e[d.i], 0, pos_sep(d.t_e[d.i]) - 1);
		if (ft_strncmp(sub, var, ft_strlen(var) + 1))
		{
			(*env)[d.k] = malloc ((ft_strlen(d.t_e[d.i]) + 1) * sizeof(char));
			if (!(*env))
				return (ft_free_dbl_str(&d.t_e), 1);
			ft_strlcpy((*env)[d.k++], d.t_e[d.i], ft_strlen(d.t_e[d.i]) + 1);
		}
		free(sub);
	}
	return ((*env)[d.k] = NULL, ft_free_dbl_str(&d.t_e), 0);
}
