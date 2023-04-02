/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 01:34:52 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/02 16:00:59 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

static int	get_name_lenght(char *line)
{
	int	i;

	i = 0;
	while (is_valid_varname(line[i]))
		i++;
	if (line[i] == '=' || !ft_strncmp(&line[i], "+=", 2) || line[i] == '\0')
		return (i);
	return (-1);
}

int	remove_line_in_env(char ***env, char *line, int name_ln)
{
	char	tmp;

	tmp = line[name_ln];
	line[name_ln] = '\0';
	if (env_del(env, line))
		return (line[name_ln] = tmp, 1);
	return (line[name_ln] = tmp, 0);
}

int	get_and_put_var(t_env *env, t_msh *msh, char *name)
{
	env->name_ln = get_name_lenght(name);
	if (env->name_ln >= 0)
	{
		env->mod = get_env_mod(name[env->name_ln]);
		env->value = name + env->name_ln + env->mod + 1;
		if (get_full_var_str(name, env, msh))
			return (1);
		if (env->src == ENV_LCL)
			if (remove_line_in_env(&msh->envp_lcl, name, env->name_ln))
				return (1);
		env->dest = ENV_EXP;
		if (put_env_var(env, msh))
			return (1);
	}
	else
		return (-1);
	return (0);
}
