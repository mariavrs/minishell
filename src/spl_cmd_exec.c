/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 23:25:09 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/07 23:37:37 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

extern int	g_exit_status;

typedef struct s_search_bin
{
	char	**path_split;
	char	*path_val;
	char	*full_name;
	int		name_len;
}	t_path;

static void	run_bin(char *full_name, t_msh *msh, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		execve(full_name, cmd->argv, msh->envp);
		ft_putstr_fd("minishell: ", 2);
		perror(full_name);
		exit(126);
	}
	else
		waitpid(pid, &g_exit_status, 0);
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	else if (WIFSIGNALED(g_exit_status))
		g_exit_status = 128 + WTERMSIG(g_exit_status);
}

static char	*bin_get_full_name(char *path, char *argv, int name_len)
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
		malloc_error();
	return (full_name);
}

static int	search_in_path(t_msh *msh, t_cmd *cmd)
{
	t_path	pb;
	int		i;

	i = -1;
	if (env_get(&pb.path_val, "PATH", msh))
		return (malloc_error(), 1);
	if (!pb.path_val)
		return (ft_mini_perror(*cmd->argv, NULL, "No such file or directory\n", 1),
			g_exit_status = 127);
	pb.path_split = ft_split(pb.path_val, ':');
	ft_free_str(&pb.path_val);
	if (!pb.path_split)
		return (malloc_error(), 1);
	pb.full_name = NULL;
	pb.name_len = ft_strlen(*cmd->argv);
	while (pb.path_split[++i] && !pb.full_name)
		pb.full_name = bin_get_full_name(pb.path_split[i], *cmd->argv,
				pb.name_len);
	ft_free_dbl_str(&pb.path_split);
	if (pb.full_name)
		return (run_bin(pb.full_name, msh, cmd),
			ft_free_str(&pb.full_name), 0);
	return (-1);
}

static void	search_bin(t_msh *msh, t_cmd *cmd)
{
	struct stat	statbuf;

	if (**cmd->argv == '\0')
		return (g_exit_status = 127, ft_putstr_fd(": command not found\n", 2));
	if (ft_strchr(*cmd->argv, '/'))
	{
		if (stat(*cmd->argv, &statbuf))
			return (g_exit_status = 127,
				ft_putstr_fd("minishell: ", 2), perror(*cmd->argv));
		if (statbuf.st_mode & S_IFDIR)
			return (g_exit_status = 126,
				ft_mini_perror(*cmd->argv, NULL, "Is a directory\n", 1));
		else
			run_bin(*cmd->argv, msh, cmd);
	}
	else if (search_in_path(msh, cmd) == -1)
		return (g_exit_status = 127,
			ft_mini_perror(*cmd->argv, NULL, "command not found\n", 0));
}

void	run_cmd_exec(t_msh *msh, t_cmd *cmd)
{
	if (!cmd->argv)
		return ;
	if (cmd->fd_in >= 0)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out >= 0)
		dup2(cmd->fd_out, STDOUT_FILENO);
	if (!ft_strncmp(*cmd->argv, "cd", 3))
		g_exit_status = ft_cd(msh, cmd->argv);
	else if (!ft_strncmp(*cmd->argv, "echo", 5))
		g_exit_status = ft_echo(msh, cmd->argv);
	else if (!ft_strncmp(*cmd->argv, "env", 4))
		g_exit_status = ft_env(msh, cmd->argv, 0);
	else if (!ft_strncmp(*cmd->argv, "exit", 5))
		g_exit_status = ft_exit(msh, cmd->argv);
	else if (!ft_strncmp(*cmd->argv, "export", 7))
		g_exit_status = ft_export(msh, cmd->argv);
	else if (!ft_strncmp(*cmd->argv, "pwd", 4))
		g_exit_status = ft_pwd();
	else if (!ft_strncmp(*cmd->argv, "unset", 6))
		g_exit_status = ft_unset(msh, cmd->argv);
	else
		search_bin(msh, cmd);
	dup2(msh->stdin_default, STDIN_FILENO);
	dup2(msh->stdout_default, STDOUT_FILENO);
}
