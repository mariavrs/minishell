/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:23:09 by mvorslov          #+#    #+#             */
/*   Updated: 2023/02/02 13:23:37 by mvorslov         ###   ########.fr       */
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