/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_local_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:02:11 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/01 15:51:47 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

static void	get_env_dest(t_env *env)
{
	if (env->i < 0)
		env->dest = ENV_LCL;
	else
		env->dest = env->src;
}

static int	env_var_declaration(t_env *env, int *skip, char *line, t_msh *msh)
{
	env->mod = get_env_mod(line[env->name_ln]);
	env->value = get_next_word(&line[env->name_ln + env->mod + 1],
			msh, skip);
	if (!env->value)
		return (*skip = 0, 1);
	*skip += env->name_ln + env->mod + 1;
	if (line[*skip])
		return (ft_free_str(&env->value), 0);
	if (get_full_var_str(line, env, msh))
		return (*skip = 0, msh->malloc_err_parse = 1);
	ft_free_str(&env->value);
	get_env_dest(env);
	if (put_env_var(env, msh))
		return (ft_free_str(&env->full_var), *skip = 0, msh->malloc_err_parse = 1);
	return (0);
}

int	first_wrd_check(int *skip, char *line, t_msh *msh)
{
	t_env	env;

	env.name_ln = -1;
	while (is_valid_varname(line[++env.name_ln])
		|| is_in_str(line[env.name_ln], "+="))
	{
		if (line[env.name_ln] == '='
			|| !ft_strncmp(&line[env.name_ln], "+=", 2))
		{
			return (env_var_declaration(&env, skip, line, msh));
		}
	}
	return (0);
}
