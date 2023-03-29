/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:54:40 by ede-smet          #+#    #+#             */
/*   Updated: 2023/03/29 17:57:18 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

static int	is_valid(char *str)
{
	int	i;
	int	flag;

	flag = 1;
	i = 0;
	if (str[0] >= '0' && str[0] <= '9')
		return (1);
	while (str[i] && flag && str[i] != '=')
	{
		if (str[i] == '+' || str[i] != '=')
		{
			if (str[i] == '+' && str[i + 1] && str[i + 1] == '=')
				flag = 0;
			else if (str[i] == '+')
				return (1);
			else if (!((str[i] >= 'a' && str[i] <= 'z')
					|| (str[i] >= 'A' && str[i] <= 'Z')
					|| str[i] == '_'
					|| (str[i] >= '0' && str[i] <= '9')))
				return (1);
		}
		i++;
	}
	return (0);
}

static void	exp_error(char *var, char *check, int *flag)
{
	if (!check)
		return (ft_putstr_fd("minishell: malloc error\n", 2));
	ft_putstr_fd("export: ", 2);
	write(2, "\'", 1);
	ft_putstr_fd(var, 2);
	write(2, "\'", 1);
	ft_putstr_fd(": not a valid identifier\n", 2);
	*flag = 1;
}

static void	export_env_print(t_msh *msh)
{
	int		i;
	char	*var;
	char	*value;

	i = -1;
	while (msh->envp[++i])
	{
		var = ft_substr(msh->envp[i], 0, pos_sep(msh->envp[i]) - 1);
		if (!var)
			return (ft_putstr_fd("minishell: malloc error\n", 2));
		write(1, "declare -x ", 11);
		if (pos_sep(msh->envp[i]) <= (int)ft_strlen(msh->envp[i]))
			value = msh->envp[i] + pos_sep(msh->envp[i]);
		write(1, var, ft_strlen(var));
		if (value && pos_sep(msh->envp[i]))
		{
			write(1, "=\"", 2);
			write(1, value, ft_strlen(value));
			write(1, "\"\n", 2);
		}
		else
			write(1, "\n", 1);
		ft_free_str(&var);
	}
}

static void	replace_if_value(t_env *env, t_msh *msh, char *input)
{
	if (pos_sep(input))
		env_lcl_replace(*env, msh->envp);
	else
		ft_free_str(&env->full_var);
}

static void	normal_case(t_env env, t_msh *msh, char *input)
{
	char	*name;

	name = get_var_name(input);
	env.name_ln = 0;
	while (input[env.name_ln] && input[env.name_ln] != '=')
		env.name_ln++;
	env.i = find_in_envp(env, msh->envp);
	env.i_local = find_in_envp(env, msh->envp_lcl);
	if (env.i >= 0)
		replace_if_value(&env, msh, input);
	else if (find_in_envp(env, msh->envp_lcl) > -1
		&& !pos_sep(input))
	{
		ft_free_str(&env.full_var);
		env.full_var = ft_strdup(msh->envp_lcl[env.i_local]);
		env_del(&msh->envp_lcl, input);
		env_lcl_add(env, msh, msh->envp, 1);
	}
	else if (env.i < 0)
	{
		env_del(&msh->envp_lcl, name);
		env_lcl_add(env, msh, msh->envp, 1);
	}
	ft_free_str(&name);
}

int	ft_export(t_msh *msh, char **inputs)
{
	int		i;
	t_env	env;
	int		err_flag;

	err_flag = 0;
	i = 0;
	if (!inputs[1])
		return (export_env_print(msh), 0);
	while (inputs[++i])
	{
		if (inputs[i][0] == '=' || inputs[i][0] == '+')
			exp_error(inputs[i], " ", &err_flag);
		else if (!(inputs[i][0] == '=' || inputs[i][0] == '+'))
		{
			env.full_var = ft_strdup(inputs[i]);
			if (env.full_var && !is_valid(inputs[i]))
				normal_case(env, msh, inputs[i]);
			else
			{
				exp_error(inputs[i], env.full_var, &err_flag);
				ft_free_str(&env.full_var);
			}
		}
		else
			return (1);
	}
	return (err_flag);
}

/* typedef struct s_export
{
	int		err_flag;
	char	*var;
	char	*value;
	char	*tmp_local;
	char	*tmp_val;
}	t_export;

void	init_s_export(t_export *t_exp)
{
	t_exp->var = NULL;
	t_exp->value = NULL;
	t_exp->tmp_local = NULL;
	t_exp->tmp_val = NULL;
}

int	get_var(t_export *t_exp, char *input)
{
	if (pos_sep(input))
	{
		t_exp->var = ft_substr(input, 0, pos_sep(input) - 1);
		if (!t_exp->var)
			return (ft_putstr_fd("minishell: malloc error\n", 2), 1);
	}
	else
	{
		t_exp->var = ft_strdup(input);
		if (!t_exp->var)
			return (ft_putstr_fd("minishell: malloc error\n", 2), 1);
	}
	return (0);
}

int	get_value(t_export *t_exp, char *input)
{
	if (pos_sep(input))
	{
		t_exp->value = ft_strdup(input + pos_sep(input));
		if (!t_exp->value)
			return (ft_putstr_fd("minishell: malloc error\n", 2), 1);
	}
	else
		t_exp->value = NULL;
	return (0);
}

int	get_var_and_value(t_export *t_exp, char *input)
{
	if (!get_var(t_exp, input) && !get_value(t_exp, input))
		return (0);
	return (1);
}

void	setup_env(t_env *env, t_msh *msh, char *input)
{
	env->name_ln = 0;
	while (input[env->name_ln] && input[env->name_ln] != '=')
		env->name_ln++;
	env->i = find_in_envp(*env, msh->envp);
	env->full_var = ft_strdup(input);
}

int	ft_new_export(t_msh *msh, char **inputs, int flag)
{
	t_export	t_exp;
	t_env		env;

	if (!inputs[1])
		return (export_env_print(msh), 0);
	init_s_export(&t_exp);
	if (get_var_and_value(&t_exp, inputs[1]))
		return (ft_free_str(&t_exp.var), ft_free_str(&t_exp.value), 1);
	t_exp.tmp_local = env_get(msh->envp_lcl, t_exp.var);
	if (t_exp.tmp_local && flag)
	{
		t_exp.tmp_val = ft_strdup(t_exp.value);
		ft_free_str(&t_exp.value);
		t_exp.value = ft_strjoin(t_exp.tmp_local, t_exp.tmp_val);
		env_del(&msh->envp_lcl, t_exp.var);
		ft_free_str(&t_exp.tmp_val);
	}
	setup_env(&env, msh, inputs[1]);
	if (!env_exist(msh->envp, t_exp.var))
		env_lcl_replace(env, msh->envp);
	else
		env_lcl_add(env, msh, msh->envp, 1);
	return (ft_free_str(&t_exp.var), ft_free_str(&t_exp.value), 0);
}

int	ft_export(t_msh *msh, char **inputs)
{
	return (ft_new_export(msh, inputs, 1));
}
 */
