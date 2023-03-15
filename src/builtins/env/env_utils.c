/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:23:09 by mvorslov          #+#    #+#             */
/*   Updated: 2023/03/15 00:22:24 by ede-smet         ###   ########.fr       */
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

int	env_exist(char **env, char *var)
{
	char	*value;

	value = env_get(env, var);
	if (!value)
		return (1);
	return (free(value), 0);
}

int	env_size(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		i++;
	return (i - 1);
}
