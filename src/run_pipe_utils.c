/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:24:16 by mvorslov          #+#    #+#             */
/*   Updated: 2023/03/04 19:32:02 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

void	close_fd(int fd0, int fd1)
{
	close(fd0);
	close(fd1);
}

void	run_pipe_left(int fd[2], char *line, char *del, t_msh *msh)
{
	pid_t	id;

	id = fork();
	if (id == -1)
		return (msh->exit_status = 1, perror("fork"));
	else if (id == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close_fd(fd[0], fd[1]);
		parse_pipe(line, del, msh);
		exit(msh->exit_status);
	}
	waitpid(id, &msh->exit_status, 0);
	msh->exit_status = WEXITSTATUS(msh->exit_status);
}

void	run_pipe_right(int fd[2], char *eline, char *del, t_msh *msh)
{
	pid_t	id;

	id = fork();
	if (id == -1)
		return (perror("fork"), msh->exit_status = 1, close_fd(fd[0], fd[1]));
	else if (id == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close_fd(fd[0], fd[1]);
		parse_pipe(del + 1, eline, msh);
		exit(msh->exit_status);
	}
	close_fd(fd[0], fd[1]);
	waitpid(id, &msh->exit_status, 0);
	msh->exit_status = WEXITSTATUS(msh->exit_status);
}
