/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 22:28:07 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/03 02:08:51 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

int	g_exit_status;

static int	sline_cmp_len(t_msh *msh)
{
	int	s_len;
	int	ex_s_len;

	s_len = ft_strlen(msh->sline);
	ex_s_len = ft_strlen(msh->ex_sline);
	if (s_len > ex_s_len)
		return (s_len + 1);
	else
		return (ex_s_len + 1);
}

static void	parse_exec_prep(t_msh *msh)
{
	char	*line;
	char	*eline;

	msh->malloc_err = 0;
	line = msh->sline;
	eline = line + ft_strlen(line);
	if (trim_whitespaces(&line, &eline))
		return ;
	if (!is_in_str(*msh->sline, STR_WHSPACE)
		&& ft_strncmp(msh->sline, msh->ex_sline, sline_cmp_len(msh)))
	{
		add_history(msh->sline);
		ft_free_str(&msh->ex_sline);
		msh->ex_sline = ft_strdup(msh->sline);
	}
	if (!syntax_check(line, eline))
		parse_list(line, eline, msh);
	else
		g_exit_status = 2;
}

static int	ft_parent_env_cpy(char ***env, char **envp)
{
	int		nb_env;
	int		i;

	i = -1;
	nb_env = 0;
	while (envp[nb_env])
		nb_env++;
	(*env) = NULL;
	(*env) = malloc((nb_env + 1) * sizeof(char *));
	if (!(*env))
		return (ft_putstr_fd("minishell: malloc error\n", 2), 1);
	while (envp[++i])
	{
		(*env)[i] = ft_strdup(envp[i]);
		if (!(*env)[i])
			return (ft_free_dbl_str(env),
				ft_putstr_fd("minishell: malloc error\n", 2), 1);
	}
	(*env)[i++] = NULL;
	return (0);
}

static int	msh_prep(t_msh *msh, char **envp)
{
	if (ft_parent_env_cpy(&(msh->envp), envp))
		return (1);
	msh->envp_lcl = NULL;
	msh->envp_lcl = malloc(sizeof(char *));
	if (!msh->envp_lcl)
		return (ft_free_dbl_str(&msh->envp),
			ft_putstr_fd("malloc error\n", 2), 1);
	msh->envp_lcl[0] = NULL;
	msh->ex_sline = NULL;
	msh->pipeline = NULL;
	msh->stdin_default = dup(STDIN_FILENO);
	msh->stdout_default = dup(STDOUT_FILENO);
	msh->malloc_err = 0;
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_msh	msh;

	(void)argc;
	(void)argv;
	if (msh_prep(&msh, envp))
		return (1);
	while (1)
	{
		signal_manager(MODE_INTR_CMD);
		msh.sline = NULL;
		msh.sline = readline("\033[1;36mminishell>> \033[0m");
		signal_manager(MODE_NITR);
		if (msh.sline)
		{
			if (ft_strlen(msh.sline) != 0)
				parse_exec_prep(&msh);
			ft_free_str(&msh.sline);
		}
		else
			return (ft_putstr_fd("exit\n", 1),
				ft_free_exit(&msh), g_exit_status);
	}
}
