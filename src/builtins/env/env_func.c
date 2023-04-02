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

char	*get_full_var(char *var, char *value)
{
	char	*full_var;
	int		size;
	int		error;
	int		i;

	i = -1;
	error = 0;
	size = ft_strlen(var) + ft_strlen(value) + 1;
	full_var = ft_malloc_str(size + 1, &error);
	while (full_var && i < size - 1)
	{
		while (*var)
			full_var[++i] = *var++;
		full_var[++i] = '=';
		while (*value)
			full_var[++i] = *value++;
	}
	full_var[i + 1] = '\0';
	return (full_var);
}

int	env_edit(t_msh *msh, char *var, char *value, int flag)
{
	t_env	env;

	env.full_var = get_full_var(var, value);
	env.name = ft_strdup(var);
	if (!env.name)
		return (ft_free_str(&env.full_var),
			ft_putstr_fd("minishell: malloc error\n", 2), 1);
	env.name_ln = ft_strlen(env.name);
	env.i = find_in_envp2(&env, msh);
	if (flag == ENV_EXP)
		env_lcl_replace(env, msh->envp);
	else if (flag == ENV_LCL)
		env_lcl_replace(env, msh->envp_lcl);
	return (ft_free_str(&env.name), 0);
}

char	*get_e_val(char *full_name)
{
	char	*e_val;

	if (pos_sep(full_name) > 0)
	{
		e_val = ft_strdup(full_name + pos_sep(full_name));
		if (!e_val)
			return (ft_putstr_fd("minishell: malloc error\n", 2), NULL);
	}
	else
	{
		e_val = ft_strdup("");
		if (!e_val)
			return (ft_putstr_fd("minishell: malloc error\n", 2), NULL);
	}
	return (e_val);
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
		if (!e_var)
			return (ft_putstr_fd("minishell: malloc error\n", 2), NULL);
		e_val = get_e_val(env[i]);
		if (!e_val)
			return (ft_free_str(&e_var), NULL);
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
	if (env_not_exist(*env, var))
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
