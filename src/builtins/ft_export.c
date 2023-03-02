/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/03/02 17:50:01 by ede-smet         ###   ########.fr       */
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

static int	pos_sep(char *str)
{
	int	i;

	i = -1;
	while (++i < (int)ft_strlen(str))
		if (str[i] == '=')
			return (i + 1);
	return (0);
}

static void	exp_error(char *var)
{
	ft_putstr_fd("export: ", 2);
	write(2, "\'", 1);
	ft_putstr_fd(var, 2);
	write(2, "\'", 1);
	ft_putstr_fd(": not a valid identifier\n", 2);
}

int	ft_export(t_msh *msh, char **inputs)
{
	char	**split;
	int		i;

	i = 0;
	if (!inputs[1])
		return (ft_env(*msh), 0);
	while (inputs[++i])
	{
		split = NULL;
		split = ft_split(inputs[i], '=');
		if (!split)
			return (1);
		if (!is_valid(split[0]))
		{
			if (!pos_sep(inputs[i]))
				return (ft_free_dbl_str(&split), 0);
			if (!env_exist(msh->envp, split[0]))
				env_edit(&msh->envp, split[0], inputs[i] + pos_sep(inputs[i]));
			else
				env_add(&msh->envp, inputs[i]);
		}
		else
			exp_error(split[0]);
		ft_free_dbl_str(&split);
	}
	return (0);
}
