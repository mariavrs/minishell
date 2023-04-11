/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_local_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:02:11 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/11 17:02:59 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

extern int	g_exit_status;

static void	get_env_dest(t_env *env)
{
	if (env->i < 0)
		env->dest = ENV_LCL;
	else
		env->dest = env->src;
}

static int	env_var_declaration(t_msh *msh, t_env *env, char *line)
{
	env->mod = get_env_mod(line[env->name_ln]);
	env->value = param_expansion(&line[env->name_ln + env->mod + 1],
			msh, quo_check(line[env->name_ln + env->mod + 1], 0), 1);
	if (!env->value)
		return (1);
	if (get_full_var_str(line, env, msh))
		return (1);
	ft_free_str(&env->value);
	get_env_dest(env);
	if (put_env_var(env, msh))
		return (ft_free_str(&env->full_var), 1);
	return (0);
}

static int	parse_var(t_msh *msh, char *line)
{
	t_env	env;

	env.name_ln = -1;
	while (line[++env.name_ln] && line[env.name_ln] != '+'
		&& line[env.name_ln] != '=')
	{
		if (is_in_str(line[++env.name_ln], "+="))
			return (env_var_declaration(msh, &env, line));
	}
	return (0);
}

int	lcl_var_declaration(t_msh *msh, char *line)
{
	int		start;
	int		end;
	int		quo_flag;
	char	tmp;

	start = 0;
	while (is_in_str(line[start], STR_WHSPACE))
		start++;
	while (line[start])
	{
		quo_flag = 0;
		end = start;
		while (line[end] && (!is_in_str(line[end], STR_WHSPACE) || quo_flag))
			quo_flag = quo_check(line[++end], quo_flag);
		tmp = line[end];
		line[end] = '\0';
		if (parse_var(msh, &line[start]))
			return (1);
		line[end] = tmp;
		start = end;
		while (is_in_str(line[start], STR_WHSPACE))
			start++;
	}
	return (0);
}

int	var_declar_fraction_ln(char *line)
{
	int	quo_flag;
	int	size;

	quo_flag = 0;
	size = 0;
	if (ft_isdigit(line[size]) || !line[size])
		return (0);
	while (is_valid_varname(line[size]))
		size++;
	if (!line[size] || (line[size] != '=' && ft_strncmp(&line[size], "+=", 2)))
		return (0);
	while (line[size] && (!is_in_str(line[size], STR_WHSPACE) || quo_flag))
		quo_flag = quo_check(line[++size], quo_flag);
	while (is_in_str(line[size], STR_WHSPACE))
		size++;
	if (line[size])
		return (size + var_declar_fraction_ln(&line[size]));
	return (size);
}
