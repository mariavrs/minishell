/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spl_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:49:24 by mvorslov          #+#    #+#             */
/*   Updated: 2023/03/28 22:12:12 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

int	parse_cmd_argv(char *line, int argc, t_msh *msh)
{
	char	*arg;
	int		eword;

	while (is_in_str(*line, STR_WHSPACE))
		line++;
	if (!(*line))
	{
		msh->argv = malloc(sizeof(char *) * (argc + 1));
		if (!msh->argv)
			return (ft_putstr_fd("minishell: malloc error\n", 2), 1);
		msh->argv[argc] = NULL;
		msh->argc = argc;
	}
	else
	{
		argc++;
		eword = 0;
		arg = get_next_word(line, msh, &eword);
		if (!arg || parse_cmd_argv(line + eword, argc, msh))
			return (1);
		msh->argv[argc - 1] = arg;
	}
	return (0);
}

int	run_redir(char *line, int *i, t_redir *rdr, t_msh *msh)
{
	char	*filename;
	int		l_start;
	int		status_lcl;

	l_start = *i;
	filename = NULL;
	filename = get_next_word(line, msh, i);
	if (!filename)
		return (ft_putstr_fd("minishell: malloc error\n", 2), 1);
	if (rdr->mode == '>' || rdr->mode == '+')
		status_lcl = redir_out(filename, rdr);
	else
		status_lcl = redir_in(filename, rdr, msh);
	while (l_start < *i)
		line[l_start++] = ' ';
	return (ft_free_str(&filename), status_lcl);
}

int	parse_redir(char *line, int i, t_redir *rdr, t_msh *msh)
{
	while (line[i])
	{
		while (line[i] && line[i] != '<' && line[i] != '>')
			i++;
		if (!line[i])
			return (0);
		if (line[i] && line[i] != line[i + 1])
			rdr->mode = line[i];
		else if (line[i] == '>' && line[i + 1] == '>')
			rdr->mode = '+';
		else if (line[i] == '<' && line[i + 1] == '<')
			rdr->mode = '-';
		while (line[i] == '<' || line[i] == '>')
			line[i++] = ' ';
		while (is_in_str(line[i], STR_WHSPACE))
			i++;
		if (run_redir(line, &i, rdr, msh))
			return (1);
	}
	return (0);
}

void	parse_simple_cmd(char *line, char *eline, t_msh *msh)
{
	t_redir	rdr;
	int		status_lcl;
	int		skip;

	rdr.stdin_cpy = 0;
	rdr.stdout_cpy = 0;
	skip = 0;
	trim_whitespaces(&line, &eline);
	msh->argv = NULL;
	msh->spl_cmd = ft_malloc_str(eline - line + 2, &msh->exit_status);
	if (!msh->spl_cmd)
		return ;
	ft_strlcpy(msh->spl_cmd, line, eline - line + 1);
	if (!(*msh->spl_cmd >= '0' && *msh->spl_cmd <= '9'))
		status_lcl = first_wrd_check(&skip, msh->spl_cmd, msh);
	if (!status_lcl && msh->spl_cmd[skip])
		status_lcl = parse_redir(msh->spl_cmd, skip, &rdr, msh);
	if (!status_lcl && line[skip])
		status_lcl = parse_cmd_argv(&msh->spl_cmd[skip], 0, msh);
	if (!status_lcl && line[skip])
		run_cmd_exec(msh);
	else
		msh->exit_status = status_lcl;
	redir_clean(&rdr);
	ft_free_spl_cmd(msh);
}
