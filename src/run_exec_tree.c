/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exec_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 20:26:56 by mvorslov          #+#    #+#             */
/*   Updated: 2023/02/15 16:45:19 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

void	run_spl_cmd(t_spl_cmd *cmd, int *exit_status, char **envp)
{
	int	i;

	i = -1;
	*exit_status = 0;
	while (++i < cmd->redirc)
	{
		if (cmd->redir[i].mode == '>' || cmd->redir[i].mode == '+')
			redir_out(cmd, i);
		else
			redir_in(cmd, i);
		close(cmd->redir[i].fd);
	}
	run_exec(cmd, exit_status, envp);
	redir_clean(cmd);
}

void	run_pipe(t_pipe *cmd, int *exit_status, char **envp)
{
	int		fd[2];
	pid_t	id[2];

	pipe(fd);
	//if (pipe(fd) == -1)
		//stop everything, pipe didn't work
	id[0] = fork();
	if (id[0] == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
//		close(1);
		close(fd[0]);
		close(fd[1]);
		ft_exec_tree(cmd->left, exit_status, envp);
		exit(*exit_status);
	}
	id[1] = fork();
	if (id[1] == 0)
	{
		dup2(fd[0], STDIN_FILENO);
//		close(0);
		close(fd[0]);
		close(fd[1]);
		ft_exec_tree(cmd->right, exit_status, envp);
		exit(*exit_status);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(id[0], exit_status, 0); //modify the option later
	waitpid(id[1], exit_status, 0); //modify the option later
}

void	run_list(t_lol *cmd, int *exit_status, char **envp)
{
	ft_exec_tree(cmd->left, exit_status, envp);
	if (*exit_status && cmd->mode == '|')
		ft_exec_tree(cmd->right, exit_status, envp);
	else if (!(*exit_status) && cmd->mode == '&')
		ft_exec_tree(cmd->right, exit_status, envp);
}

void	ft_exec_tree(t_cmd *cmd, int *exit_status, char **envp)
{
	if (!cmd)
		return ;
	else if (cmd->type == EXEC_CMD)
		run_spl_cmd((t_spl_cmd *)cmd, exit_status, envp);
	else if (cmd->type == PIPE_CMD)
		run_pipe((t_pipe *)cmd, exit_status, envp);
	else if (cmd->type == LIST_CMD)
		run_list((t_lol *)cmd, exit_status, envp);
}
