/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 23:25:09 by mvorslov          #+#    #+#             */
/*   Updated: 2023/02/22 17:34:36 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

void	run_exec_bin(char **argv, t_msh *msh)
{
	char	*full_fun_name;

	full_fun_name = ft_strjoin("/usr/bin/", *argv);
	if (fork() == 0)
		execve(full_fun_name, argv, msh->envp);
	else
		wait(&msh->exit_status);
	free(full_fun_name);
}

int	run_search_bin(char **argv, t_msh *msh)
{
	DIR	*bin_lib;
	struct dirent *bin_lib_obj;

	bin_lib = NULL;
	bin_lib = opendir("/usr/bin");
/* 	if (!bin_lib)
		panic open didn't work, quit everything */
	bin_lib_obj = readdir(bin_lib);
	while (bin_lib_obj && ft_strncmp(bin_lib_obj->d_name, *argv, ft_strlen(*argv) + 1))
		bin_lib_obj = readdir(bin_lib);
	closedir(bin_lib);
	if (bin_lib_obj) // I'm not sure if we have to check the type
		run_exec_bin(argv, msh);
	else
		return (1);
	return (0);
}

void	run_exec(t_spl_cmd *cmd, t_msh *msh)
{
	if (!ft_strncmp(cmd->argv[0], "cd", 3))
		ft_cd();
	else if (!ft_strncmp(cmd->argv[0], "echo", 5))
		ft_echo();
	else if (!ft_strncmp(cmd->argv[0], "env", 4))
		ft_env();
	else if (!ft_strncmp(cmd->argv[0], "exit", 5))
		ft_exit();
	else if (!ft_strncmp(cmd->argv[0], "export", 7))
		ft_export();
	else if (!ft_strncmp(cmd->argv[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(cmd->argv[0], "unset", 6))
		ft_unset();
	else if (run_search_bin(cmd->argv, msh))
	{
		printf("minishell: %s: command not found\n", cmd->argv[0]);//modify with strerror or perror
		msh->exit_status = 127;
	}
}

void	run_spl_cmd(t_spl_cmd *cmd, t_msh *msh)
{
	int	i;

	i = -1;
	msh->exit_status = 0;
	while (++i < cmd->redirc && msh->exit_status == 0)
	{
		if (cmd->redir[i].mode == '>' || cmd->redir[i].mode == '+')
			msh->exit_status = redir_out(cmd, i);
		else
			msh->exit_status = redir_in(cmd, i);
		close(cmd->redir[i].fd);
	}
	ft_free_redir_info(cmd);
	if (msh->exit_status == 0)
		run_exec(cmd, msh);
	ft_free_argv(cmd);
	redir_clean(cmd);
}
