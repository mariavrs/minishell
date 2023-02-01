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

void ft_fill_env(char *env, char *var, char *value)
{
	int	i;
	int k;

	i = -1;
	while (i < (int)(ft_strlen(var) + ft_strlen(value) + 1))
	{
		k = -1;
		while (++k < (int)ft_strlen(var))
			env[i++] = var[k];
		env[i] = '=';
		k = -1;
		while (++k < (int)ft_strlen(value))
			env[i++] = var[k];
		env[i] = '\0';
	}
}

void	free_table(char **table)
{
	int	i;

	i = -1;
	if (!table)
		return ;
	while (table[++i])
		free(table[i]);
	free(table);
}

int	env_edit(char **env, char *var, char *value)
{
	int		i;
	char	**tmp;

	i = -1;
	tmp = NULL;
	while (env[++i])
	{
		tmp = ft_split(env[i], '=');
		if (ft_strncmp(tmp[0], var, ft_strlen(var)))
		{
			free(env[i]);
			env[i] = NULL;
			env[i] = malloc((ft_strlen(tmp[0]) + ft_strlen(value) + 2) * sizeof(char));
			if (env[i])
				return (1);
			ft_fill_env(env[i], tmp[0], value);
		}
		free_table(tmp);
	}
	return (0);
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
