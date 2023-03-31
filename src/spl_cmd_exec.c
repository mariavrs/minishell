/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 23:25:09 by mvorslov          #+#    #+#             */
/*   Updated: 2023/03/31 16:25:00 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

extern int	g_exit_status;

void	run_bin(char *full_name, t_msh *msh)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		exit(execve(full_name, msh->argv, msh->envp));
	}
	else
		waitpid(pid, &g_exit_status, 0);
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	else if (WIFSIGNALED(g_exit_status))
		g_exit_status = 128 + WTERMSIG(g_exit_status);
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

int	search_in_path(t_msh *msh)
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
	pb.name_len = ft_strlen(msh->argv[0]);
	while (pb.path_split[++i] && !pb.full_name)
		pb.full_name = bin_get_full_name(pb.path_split[i], msh->argv[0],
				pb.name_len);
	ft_free_dbl_str(&pb.path_split);
	if (pb.full_name)
		return (run_bin(pb.full_name, msh),
			ft_free_str(&pb.full_name), 0);
	return (1);
}

void	search_bin(t_msh *msh)
{
	struct stat	statbuf;

	if (ft_strchr(msh->argv[0], '/'))
	{
		if (!stat(msh->argv[0], &statbuf))
		{
			if (statbuf.st_mode & S_IFDIR)
				return (g_exit_status = 126,
					error_search_bin(msh->argv[0], ": Is a directory\n"));
			else
				run_bin(msh->argv[0], msh);
		}
		else
		{
			return (g_exit_status = 127,
				error_search_bin(msh->argv[0], ": No such file or directory\n"));
		}
	}
	else if (search_in_path(msh))
	{
		return (g_exit_status = 127,
			error_search_bin(msh->argv[0], ": command not found\n"));
	}
}

void	run_cmd_exec(t_msh *msh)
{
	if (!ft_strncmp(msh->argv[0], "cd", 3))
		g_exit_status = ft_cd(msh->argv, msh);
	else if (!ft_strncmp(msh->argv[0], "echo", 5))
		g_exit_status = ft_echo(msh->argv);
	else if (!ft_strncmp(msh->argv[0], "env", 4))
		g_exit_status = ft_env(*msh, 0);
	else if (!ft_strncmp(msh->argv[0], "exit", 5))
		g_exit_status = ft_exit(msh->argv, msh);
	else if (!ft_strncmp(msh->argv[0], "export", 7))
		g_exit_status = ft_export(msh, msh->argv);
	else if (!ft_strncmp(msh->argv[0], "pwd", 4))
		g_exit_status = ft_pwd();
	else if (!ft_strncmp(msh->argv[0], "unset", 6))
		g_exit_status = ft_unset(msh, msh->argv);
	else
		search_bin(msh);
}
