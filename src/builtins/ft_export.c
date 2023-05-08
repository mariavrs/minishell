/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/13 18:28:59 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

static int	get_name_lenght(char *line)
{
	int	i;

	i = 0;
	while (is_valid_varname(line[i]) && !ft_isdigit(line[0]))
		i++;
	if (line[i] == '=' || !ft_strncmp(&line[i], "+=", 2) || line[i] == '\0')
		return (i);
	return (-1);
}

static int	get_and_put_var(t_env *env, t_msh *msh, char *name)
{
	env->name_ln = get_name_lenght(name);
	if (env->name_ln >= 0)
	{
		env->name = name;
		env->mod = get_env_mod(name[env->name_ln]);
		env->value = name + env->name_ln + env->mod + 1;
		if (get_full_var_str(name, env, msh))
			return (1);
		if (env->src == ENV_LCL)
			if (env_remove_line(msh, *env, msh->envp_lcl))
				return (1);
		env->dest = ENV_EXP;
		if (put_env_var(env, msh))
			return (1);
	}
	else
		return (-1);
	return (0);
}

static int	export_env_print(t_msh *msh)
{
	int		i;
	char	*var;
	char	*value;

	i = -1;
	while (msh->envp[++i])
	{
		var = ft_substr(msh->envp[i], 0, env_val_start_pos(msh->envp[i]) - 1);
		if (!var)
			return (malloc_error(), 1);
		write(1, "declare -x ", 11);
		if (env_val_start_pos(msh->envp[i]) <= (int)ft_strlen(msh->envp[i]))
			value = msh->envp[i] + env_val_start_pos(msh->envp[i]);
		write(1, var, ft_strlen(var));
		if (value && env_val_start_pos(msh->envp[i]))
		{
			write(1, "=\"", 2);
			write(1, value, ft_strlen(value));
			write(1, "\"\n", 2);
		}
		else
			write(1, "\n", 1);
		ft_free_str(&var);
	}
	return (0);
}

typedef struct s_ft_export
{
	t_env	env;
	int		err_flag;
	int		i;
	int		status;
}	t_ft_export;

int	ft_export(t_msh *msh, char **argv)
{
	t_ft_export	exp;

	exp.env.name_ln = -1;
	exp.err_flag = 0;
	exp.i = 0;
	if (!argv[1])
	{
		if (export_env_print(msh))
			return (ft_exit_error(0, NULL, msh, ERR_MALLOC), ERR_MALLOC);
		return (0);
	}
	while (argv[++exp.i])
	{
		if (argv[exp.i][0] == '=' || argv[exp.i][0] == '\0')
			error_export(argv[exp.i], &exp.err_flag);
		else
		{
			exp.status = get_and_put_var(&exp.env, msh, argv[exp.i]);
			if (exp.status == -1)
				error_export(argv[exp.i], &exp.err_flag);
			else if (exp.status == 1)
				return (ft_exit_error(0, NULL, msh, ERR_MALLOC), ERR_MALLOC);
		}
	}
	return (exp.err_flag);
}
