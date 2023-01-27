/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exec_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 20:26:56 by mvorslov          #+#    #+#             */
/*   Updated: 2023/01/27 12:41:20 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

void	run_exec(t_exec *cmd, int *exit_status)
{
	*exit_status = 0;
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
	else
	{
		printf("minishell: %s: command not found :(\n", cmd->argv[0]);
		*exit_status = 127;
	}
/* 	while (*(cmd->argv))
		printf("%s\n", *(cmd->argv)++); */
}

void	run_redir(t_redir *cmd, int *exit_status)
{
	(void)cmd;
	(void)exit_status;
}

void	run_pipe(t_pipe *cmd, int *exit_status)
{
	(void)cmd;
	(void)exit_status;
/* 	int		fd[2];
	pid_t	id[2];

	pipe(fd);
	//if (pipe(fd) == -1)
		//stop everything, pipe didn't work
	id[0] = fork();
	if (id[0] == 0)
	{
		close(1);
		dup(fd[1]);
		close(fd[0]);
		close(fd[1]);
		ft_exec_tree(cmd->left, exit_status);
	}
	else
	{
		id[1] = fork();
		if (id[1] == 0)
		{
			close(0);
			dup(fd[0]);
			close(fd[0]);
			close(fd[1]);
			ft_exec_tree(cmd->right, exit_status);
		}
		else
		{
			waitpid(id[0], exit_status, 0); //modify the option later
			waitpid(id[1], exit_status, 0);
		}
	} */
}

void	run_list(t_lol *cmd, int *exit_status)
{
	ft_exec_tree(cmd->left, exit_status);
	if (*exit_status && cmd->mode == '|')
		ft_exec_tree(cmd->right, exit_status);
	else if (!(*exit_status) && cmd->mode == '&')
		ft_exec_tree(cmd->right, exit_status);
}
