/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/03/06 15:59:56 by ede-smet         ###   ########.fr       */
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

static void	exp_error(char *var)
{
	ft_putstr_fd("export: ", 2);
	write(2, "\'", 1);
	ft_putstr_fd(var, 2);
	write(2, "\'", 1);
	ft_putstr_fd(": not a valid identifier\n", 2);
}

static void	export_env_print(t_msh *msh)
{
	char	*line_1;
	char	*line_2;
	char	*value;
	char	*var;
	int		i;

	i = -1;
	value = NULL;
	line_2 = NULL;
	while (msh->envp[++i])
	{
		var = ft_substr(msh->envp[i], 0, pos_sep(msh->envp[i]) - 1);
		if (pos_sep(msh->envp[i]) <= (int)ft_strlen(msh->envp[i]))
			value = ft_strdup(msh->envp[i] + pos_sep(msh->envp[i]));
		line_1 = ft_strjoin("declare -x ", var);
		if (value && pos_sep(msh->envp[i]))
		{
			line_2 = ft_strjoin(line_1, "=\"");
			ft_free_str(&line_1);
			line_1 = ft_strjoin(line_2, value);
			ft_free_str(&line_2);
			line_2 = ft_strjoin(line_1, "\"");
			printf("%s\n", line_2);
		}
		else
			printf("%s\n", line_1);
		ft_free_str(&var);
		ft_free_str(&value);
		ft_free_str(&line_2);
		ft_free_str(&line_1);
	}
}

int	ft_export(t_msh *msh, char **inputs)
{
	char	*e_var;
	int		i;

	i = 0;
	if (!inputs[1])
		return (export_env_print(msh), 0);
	while (inputs[++i])
	{
		e_var = ft_substr(inputs[i], 0, pos_sep(inputs[i]) - 1);
		if (!is_valid(e_var))
		{
			if (!env_exist(msh->envp, e_var) && pos_sep(inputs[i]) > 0)
				env_edit(&msh->envp, e_var, inputs[i] + pos_sep(inputs[i]));
			else if (env_exist(msh->envp, e_var))
				env_add(&msh->envp, inputs[i]);
		}
		else
			exp_error(e_var);
		ft_free_str(&e_var);
	}
	return (0);
}
