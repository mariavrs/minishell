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

typedef struct env_func
{
	char	*env_var;
	char	**env_tmp;
	int		i;
	int		j;
}	t_ef;

int	env_edit(char ***env, char *var, char *value)
{
	int		i;
	char	*env_var;

	i = -1;
	while ((*env)[++i])
	{
		env_var = ft_substr((*env)[i], 0, pos_sep((*env)[i]) - 1);
		if (!env_var)
			return (1);
		if (!ft_strncmp(env_var, var, ft_strlen(var) + 1))
		{
			ft_free_str(&(*env)[i]);
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
		if (!e_var || !e_val)
			return (ft_putstr_fd("minishell: malloc error\n", 2), NULL);
		if (!ft_strncmp(e_var, var, ft_strlen(var) + 1))
			return (ft_free_str(&e_var), e_val);
		ft_free_str(&e_var);
		ft_free_str(&e_val);
	}
	return (NULL);
}

int	env_del(char ***env, char *var)
{
	t_ef	ef;

	ef.i = -1;
	ef.j = -1;
	if (env_exist(*env, var))
		return (1);
	ef.env_tmp = NULL;
	ef.env_tmp = malloc (env_size(*env) * sizeof(char *));
	if (!ef.env_tmp)
		return (ft_putstr_fd("minishell: malloc error\n", 2), 1);
	while ((*env)[++ef.i])
	{
		ef.env_tmp[ef.j + 1] = NULL;
		ef.env_var = ft_substr((*env)[ef.i], 0, pos_sep((*env)[ef.i]) - 1);
		if (!ef.env_var)
			return (ft_free_dbl_str(&ef.env_tmp),
				ft_putstr_fd("minishell: malloc error\n", 2), 1);
		if (ft_strncmp(ef.env_var, var, ft_strlen(var) + 1))
			ef.env_tmp[++ef.j] = (*env)[ef.i];
		else
			ft_free_str(&(*env)[ef.i]);
		ft_free_str(&ef.env_var);
	}
	return (ef.env_tmp[++ef.j] = NULL, free(*env),
		*env = ef.env_tmp, 0);
}

char	*get_var_name(char *input)
{
	char	*var_name;

	var_name = NULL;
	var_name = ft_substr(input, 0, pos_sep(input) - 1);
	if (!var_name)
		return (ft_putstr_fd("minishell: malloc error\n", 2), NULL);
	return (var_name);
}

int	check_append_charset(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
			if (str[++i] && str[i] == '=')
				return (i - 1);
		i++;
	}
	return (0);
}
