/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 23:26:27 by mvorslov          #+#    #+#             */
/*   Updated: 2023/02/22 02:28:10 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

static int	ft_intlen(unsigned int n)
{
	int	len;

	len = 1;
	while (n >= 10)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa_local(unsigned int n)
{
	char	*str;
	int		len;

	len = ft_intlen(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len--] = '\0';
	while (len >= 0)
	{
		str[len--] = n % 10 + 48;
		n = n / 10;
	}
	return (str);
}

void	redir_heredoc(t_spl_cmd *cmd, int i)
{
	t_heredoc	hd;

	fstat(STDIN_FILENO, &hd.statbuf);
	hd.hdoc_id = ft_itoa_local(hd.statbuf.st_atim.tv_sec);
	hd.hdoc = ft_strjoin("/tmp/minishell-", hd.hdoc_id);
	free(hd.hdoc_id);
	printf("%s\n", hd.hdoc);
	cmd->redir[i].fd = open(hd.hdoc, O_CREAT | O_WRONLY | O_APPEND | O_TRUNC, 0444);
	if (cmd->redir[i].fd < 0)
		perror("open");
	hd.line = NULL;
	hd.line = readline("> ");
	while (ft_strncmp(hd.line, cmd->redir[i].file,
		ft_strlen(cmd->redir[i].file) + 1))
	{
		ft_putstr_fd(hd.line, cmd->redir[i].fd);
		write(cmd->redir[i].fd, "\n", 1);
		hd.line = readline("> ");
	}
	close(cmd->redir[i].fd);
	cmd->redir[i].fd = open(hd.hdoc, O_RDONLY);
	if (cmd->redir[i].fd < 0)
		perror("open");
	unlink(hd.hdoc);
	free(hd.hdoc);
}

void	redir_in(t_spl_cmd *cmd, int i)
{
	if (!cmd->stdin_cpy)
		cmd->stdin_cpy = dup(STDIN_FILENO);
	if (cmd->redir[i].mode == '<')
		cmd->redir[i].fd = open(cmd->redir[i].file, O_RDONLY);
	else if (cmd->redir[i].mode == '-')
		redir_heredoc(cmd, i);
	dup2(cmd->redir[i].fd, STDIN_FILENO);
}

void	redir_out(t_spl_cmd *cmd, int i)
{
	if (!cmd->stdout_cpy)
		cmd->stdout_cpy = dup(STDOUT_FILENO);
	if (cmd->redir[i].mode == '>')
		cmd->redir[i].fd = open(cmd->redir[i].file,
			O_CREAT | O_RDWR | O_TRUNC, 0664);
	else if (cmd->redir[i].mode == '+')
		cmd->redir[i].fd = open(cmd->redir[i].file,
			O_CREAT | O_RDWR | O_APPEND, 0664);
	dup2(cmd->redir[i].fd, STDOUT_FILENO);
}

void	redir_clean(t_spl_cmd *cmd)
{
	if (cmd->stdin_cpy)
	{
		dup2(cmd->stdin_cpy, STDIN_FILENO);
		close(cmd->stdin_cpy);
	}
	if (cmd->stdout_cpy)
	{
		dup2(cmd->stdout_cpy, STDOUT_FILENO);
		close(cmd->stdout_cpy);
	}
}
