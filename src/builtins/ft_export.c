/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/02/12 23:14:40 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

static int	is_valid(char *str)
{
	if (str[0] >= '0' && str[0] <= '9')
		return (1);
	while (*str)
	{
		if (!((*str >= 'a' && *str <= 'z')
				|| (*str >= 'A' && *str <= 'Z')
				|| *str == '_'
				|| (*str >= '0' && *str <= '9')))
			return (1);
		str++;
	}
	return (0);
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

int	ft_export(char ***env, char **inputs)
{
	char	**split;
	int		i;

	i = 0;
	while (inputs[++i])
	{
		split = NULL;
		split = ft_split(inputs[i], '=');
		if (!is_valid(split[0]))
		{
			if (!pos_sep(inputs[i]))
				return (free_table(split), 0);
			env_add(env, inputs[i]);
		}
		else
		{
			ft_putstr_fd("export: ", 2);
			write(2, "\'", 1);
			ft_putstr_fd(split[0], 2);
			write(2, "\'", 1);
			ft_putstr_fd(": not a valid identifier\n", 2);
		}
		free_table(split);
	}
	return (0);
}
