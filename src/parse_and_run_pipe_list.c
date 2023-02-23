/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_run_pipe_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:28:59 by mvorslov          #+#    #+#             */
/*   Updated: 2023/02/23 16:05:14 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

void	close_fd(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}

void	run_pipe(char *line, char *eline, char *del, t_msh *msh)
{
	int		fd[2];
	pid_t	id[2];

	pipe(fd);
	if (pipe(fd) == -1)
		return (perror("pipe"));
	id[0] = fork();
	if (id[0] == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close_fd(fd[0], fd[1]);
		parse_pipe(line, del, msh);
		exit(msh->exit_status);
	}
	id[1] = fork();
	if (id[1] == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close_fd(fd[0], fd[1]);
		parse_pipe(del + 1, eline, msh);
		exit(msh->exit_status);
	}
	close_fd(fd[0], fd[1]);
	waitpid(id[0], &msh->exit_status, 0);
	waitpid(id[1], &msh->exit_status, 0);
}

void	parse_pipe(char *line, char *eline, t_msh *msh)
{
	char	*del;
	int		quo_flag;

	trim_whitespaces(&line, &eline);
	del = eline - 1;
	quo_flag = 0;
	while (del > line
		&& ((*del != '|' && *del != '(' && *del != ')') || quo_flag))
	{
		quo_flag = quo_check(*del, quo_flag);
		del--;
	}
	if (del == line)
		return (parse_simple_cmd(line, eline, msh));
	run_pipe(line, eline, del, msh);
}

int	list_delim_locator(char *line, char *eline, char **del)
{
	int	block_check;
	int	quo_flag;

	block_check = 0;
	quo_flag = 0;
	*del = eline - 1;
	while (*del > line && !(!block_check && !quo_flag
			&& ((**del == '&' && *(*del - 1) == '&')
				|| (**del == '|' && *(*del - 1) == '|'))))
	{
		if (**del == ')' && !quo_flag)
			block_check++;
		else if (**del == '(' && !quo_flag)
			block_check--;
		else
			quo_flag = quo_check(**del, quo_flag);
		*del = *del - 1;
	}
	if (*del == line)
		return (1);
	*del = *del - 1;
	return (0);
}

void	parse_list(char *line, char *eline, t_msh *msh)
{
	char	*del;

	trim_whitespaces(&line, &eline);
	trim_brackets(&line, &eline);
	if (list_delim_locator(line, eline, &del) == 1)
		return (parse_pipe(line, eline, msh));
	parse_list(line, del, msh);
	if ((msh->exit_status == 0 && *del == '&')
		|| (msh->exit_status != 0 && *del == '|'))
		parse_list(del + 2, eline, msh);
}
