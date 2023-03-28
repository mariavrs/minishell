/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_local_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:02:11 by mvorslov          #+#    #+#             */
/*   Updated: 2023/03/26 22:29:57 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

int	get_full_var_str(char *line, t_env *env)
{
	char	tmp;

	tmp = line[env->name_ln + 1];
	line[env->name_ln + 1] = '\0';
	env->full_var = ft_strjoin(line, env->value);
	ft_free_str(&env->value);
	line[env->name_ln + 1] = tmp;
	if (!env->full_var)
		return (ft_putstr_fd("minishell: malloc error\n", 2), 1);
	return (0);
}

/* char	*get_var_value(char *cursor)
{
	char	*str;
	int		symb_count;

	str = NULL;
	symb_count = wrd_collect(cursor, 0);
	str = malloc(sizeof(char) * (symb_count + 1));
	if (!str)
		return (ft_putstr_fd("minishell: malloc error\n", 2), NULL);
	str[symb_count] = '\0';
	while (--symb_count >= 0)
		str[symb_count] = *(cursor + symb_count);
	return (str);
} */

int	first_wrd_check(int *skip, char *line, t_msh *msh)
{
	t_env	env;

	env.name_ln = -1;
	while (is_valid_varname(line[++env.name_ln]) || line[env.name_ln] == '=')
	{
		if (line[env.name_ln] == '=')
		{
			env.value = get_next_word(&line[env.name_ln + 1], msh, skip);
			if (!env.value)
				return (*skip = 0, 1);
			*skip += env.name_ln + 1;
			if (line[*skip])
				return (ft_free_str(&env.value), 0);
			if (get_full_var_str(line, &env))
				return (*skip = 0, 1);
			env.i = find_in_envp(env, msh->envp_lcl);
			if (env.i >= 0 && env_lcl_replace(env, msh->envp_lcl))
				return (ft_free_str(&env.full_var), *skip = 0, 1);
			else if (env.i < 0 && env_lcl_add(env, msh, msh->envp_lcl, 0))
				return (ft_free_str(&env.full_var), *skip = 0, 1);
			return (0);
		}
	}
	return (0);
}
