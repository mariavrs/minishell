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
			return (ft_free_str(&e_var), e_val);
		ft_free_str(&e_var);
		ft_free_str(&e_val);
	}
	return (NULL);
}

int	env_del(char ***env, char *var)
{
	char	*env_var;
	char	**env_tmp;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (env_exist(*env, var))
		return (1);
	env_tmp = malloc (env_size(*env) * sizeof(char *));
	if (!env_tmp)
		return (1);
	while ((*env)[++i])
	{
		env_var = ft_substr((*env)[i], 0, pos_sep((*env)[i]) - 1);
		if (ft_strncmp(env_var, var, ft_strlen(var) + 1))
			env_tmp[++j] = (*env)[i];
		else
			ft_free_str(&(*env)[i]);
		ft_free_str(&env_var);
	}
	env_tmp[++j] = NULL;
	free(*env);
	*env = env_tmp;
	return (0);
}
