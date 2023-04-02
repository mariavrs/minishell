/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:23:09 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/02 01:46:37 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/mini_fun.h"

int	env_not_exist(char **env, char *var)
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
