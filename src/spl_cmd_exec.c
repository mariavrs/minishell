/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 23:25:09 by mvorslov          #+#    #+#             */
/*   Updated: 2023/03/30 13:29:01 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

extern pid_t	g_pid;

void	run_bin(char *full_name, char **argv, t_msh *msh)
{
	g_pid = fork();
	sig_handler(2);
	if (g_pid == 0)
		exit(execve(full_name, argv, msh->envp));
	else
		waitpid(g_pid, &msh->exit_status, 0);
	msh->exit_status = WEXITSTATUS(msh->exit_status);
}

char	*bin_get_full_name(char *path, char *argv, int name_len)
{
	int			path_len;
	char		*full_name;
	struct stat	statbuf;

	path_len = ft_strlen(path);
	full_name = malloc(sizeof(char) * (path_len + name_len + 2));
	if (full_name)
	{
		ft_strlcpy(full_name, path, path_len + 1);
		full_name[path_len] = '/';
		ft_strlcpy(&full_name[path_len + 1], argv, name_len + 1);
		if (stat(full_name, &statbuf))
			ft_free_str(&full_name);
	}
	else
		ft_putstr_fd("minishell: malloc error\n", 2);
	return (full_name);
}

int	search_in_path(char **argv, t_msh *msh)
{
	t_path	pb;
	int		i;

	i = -1;
	pb.path_val = env_get(msh->envp_lcl, "PATH");
	if (!pb.path_val)
		pb.path_val = env_get(msh->envp, "PATH");
	if (!pb.path_val)
		return (1);
	pb.path_split = ft_split(pb.path_val, ':');
	ft_free_str(&pb.path_val);
	if (!pb.path_split)
		return (ft_putstr_fd("minishell: malloc error \n", 2), 1);
	pb.full_name = NULL;
	pb.name_len = ft_strlen(argv[0]);
	while (pb.path_split[++i] && !pb.full_name)
		pb.full_name = bin_get_full_name(pb.path_split[i], argv[0],
				pb.name_len);
	ft_free_dbl_str(&pb.path_split);
	if (pb.full_name)
		return (run_bin(pb.full_name, argv, msh),
			ft_free_str(&pb.full_name), 0);
	return (1);
}

int	search_bin(char **argv, t_msh *msh)
{
	struct stat	statbuf;

	if (ft_strchr(argv[0], '/'))
	{
		if (!stat(argv[0], &statbuf))
			run_bin(argv[0], argv, msh);
		else
			return (1);
	}
	else
		if (search_in_path(argv, msh))
			return (1);
	return (0);
}

void	run_cmd_exec(t_msh *msh)
{
	if (!ft_strncmp(msh->argv[0], "cd", 3))
		msh->exit_status = ft_cd(msh->argv, msh);
	else if (!ft_strncmp(msh->argv[0], "echo", 5))
		msh->exit_status = ft_echo(msh->argv);
	else if (!ft_strncmp(msh->argv[0], "env", 4))
		msh->exit_status = ft_env(*msh, 0);
	else if (!ft_strncmp(msh->argv[0], "exit", 5))
		msh->exit_status = ft_exit(msh->argv, msh);
	else if (!ft_strncmp(msh->argv[0], "export", 7))
		msh->exit_status = ft_export(msh, msh->argv);
	else if (!ft_strncmp(msh->argv[0], "pwd", 4))
		msh->exit_status = ft_pwd();
	else if (!ft_strncmp(msh->argv[0], "unset", 6))
		msh->exit_status = ft_unset(msh, msh->argv);
	else if (search_bin(msh->argv, msh))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(msh->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		msh->exit_status = 127;
	}
}
