/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 23:25:09 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/12 19:37:45 by mvorslov         ###   ########.fr       */
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
	if (pid == -1)
	{
		g_exit_status = ERR_FORK;
		perror("minishell");
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		execve(full_name, cmd->argv, msh->envp);
		ft_putstr_fd("minishell: ", 2);
		perror(full_name);
		exit(126);
	}
	else
		g_exit_status = waitpid_collect_status(pid);
}

static char	*bin_get_full_name(t_msh *msh, char *path, char *argv, int name_len)
{
	int			path_len;
	char		*full_name;
	struct stat	statbuf;

	path_len = ft_strlen(path);
	full_name = ft_malloc_str(path_len + name_len + 2);
	if (full_name)
	{
		ft_strlcpy(full_name, path, path_len + 1);
		full_name[path_len] = '/';
		ft_strlcpy(&full_name[path_len + 1], argv, name_len + 1);
		if (stat(full_name, &statbuf))
			ft_free_str(&full_name);
	}
	else
	{
		if (!msh->pipe_flag)
			ft_putendl_fd("exit", 1);
		ft_free_exit(msh);
		exit(ERR_MALLOC);
	}
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
		return (cmd->error_msg = cmd_error_msg("minishell", *cmd->argv,
				"No such file or directory", msh), g_exit_status = 127);
	pb.path_split = ft_split(pb.path_val, ':');
	ft_free_str(&pb.path_val);
	if (!pb.path_split)
		return (malloc_error(), 1);
	pb.full_name = NULL;
	pb.name_len = ft_strlen(*cmd->argv);
	while (pb.path_split[++i] && !pb.full_name)
		pb.full_name = bin_get_full_name(msh, pb.path_split[i], *cmd->argv,
				pb.name_len);
	ft_free_dbl_str(&pb.path_split);
	if (pb.full_name)
		return (run_bin(pb.full_name, msh, cmd),
			ft_free_str(&pb.full_name), 0);
	if (g_exit_status)
		return (g_exit_status);
	return (-1);
}

static void	search_bin(t_msh *msh, t_cmd *cmd)
{
	struct stat	statbuf;

	if (**cmd->argv == '\0')
		return (g_exit_status = 127, cmd->error_msg = cmd_error_msg("''",
				NULL, "command not found", msh), (void)statbuf);
	if (ft_strchr(*cmd->argv, '/'))
	{
		if (stat(*cmd->argv, &statbuf))
			return (g_exit_status = 127,
				ft_putstr_fd("minishell: ", 2), perror(*cmd->argv));
		if (statbuf.st_mode & S_IFDIR)
			return (g_exit_status = 126,
				ft_mini_perror(*cmd->argv, NULL, "Is a directory", 1));
		else
			run_bin(*cmd->argv, msh, cmd);
	}
	else if (!ft_strncmp(*cmd->argv, ".", 2) || !ft_strncmp(*cmd->argv, "..", 3)
		|| search_in_path(msh, cmd) == -1)
		return (g_exit_status = 127, cmd->error_msg = cmd_error_msg(*cmd->argv,
				NULL, "command not found", msh), (void)statbuf);
}

void	run_cmd_exec(t_msh *msh, t_cmd *cmd)
{
	if (get_backup_stdio(msh, cmd))
		return (ft_free_exit(msh), exit(ERR_IO));
	if (run_redir(msh, cmd))
		return ;
	if (!cmd->argv)
		return (put_backup_stdio(msh, cmd));
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
	put_backup_stdio(msh, cmd);
}
