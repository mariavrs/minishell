/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spl_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:49:24 by mvorslov          #+#    #+#             */
/*   Updated: 2023/03/01 15:42:23 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

int	wrd_collect(char *line, int count)
{
	int	quo_flag;

	quo_flag = 0;
	while (line[count] && !is_in_str(line[count], STR_WHSPACE)
		&& !is_in_str(line[count], STR_REDIR))
	{
		if (is_in_str(line[count], STR_QUOTE))
		{
			quo_flag = quo_check(line[count], quo_flag);
			ft_strlcpy(line + count, line + count + 1, ft_strlen(line + count));
			while (line[count] && quo_flag)
			{
				quo_flag = quo_check(line[count], quo_flag);
				if (!quo_flag)
					ft_strlcpy(line + count, line + count + 1,
						ft_strlen(line + count));
				else
					count++;
			}
		}
		else
			count++;
	}
	return (count);
}

int	parse_cmd_argv(char *line, int argc, t_msh *msh)
{
	int	eword;

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
		eword = wrd_collect(line, 0);
		if ((line[eword] && parse_cmd_argv(line + eword + 1, argc, msh))
			|| (!line[eword] && parse_cmd_argv(line + eword, argc, msh)))
			return (1);
		line[eword] = '\0';
		msh->argv[argc - 1] = line;
	}
	return (0);
}

int	run_redir(char *line, int *i, t_redir *rdr, t_msh *msh)
{
	int		i_tmp;
	char	tmp;
	int		status_lcl;

	i_tmp = *i;
	*i += wrd_collect(&line[*i], 0);
	tmp = line[*i];
	line[*i] = '\0';
	if (rdr->mode == '>' || rdr->mode == '+')
		status_lcl = redir_out(&line[i_tmp], rdr);
	else
		status_lcl = redir_in(&line[i_tmp], rdr, msh);
	line[*i] = tmp;
	while (i_tmp < *i)
		line[i_tmp++] = ' ';
	return (status_lcl);
}

int	parse_redir(char *line, t_redir *rdr, t_msh *msh)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] != '<' && line[i] != '>')
			i++;
		if (line[i] && line[i] != line[i + 1])
			rdr->mode = line[i];
		else if (line[i] == '>' && line[i + 1] == '>')
			rdr->mode = '+';
		else if (line[i] == '<' && line[i + 1] == '<')
			rdr->mode = '-';
		while (line[i] == '<' || line[i] == '>')
		{
			line[i] = ' ';
			i++;
		}
		while (is_in_str(line[i], STR_WHSPACE))
			i++;
		if (line[i])
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
	*eline = '\0';
	msh->spl_cmd = param_expansion(line, msh);
	if (!msh->spl_cmd)
		return (ft_putstr_fd("minishell: malloc error\n", 2));
	status_lcl = parse_redir(msh->spl_cmd, &rdr, msh);
	if (!status_lcl && !(*line >= '0' && *line <= '9'))
		status_lcl = first_wrd_check(&skip, msh->spl_cmd, msh);
	if (!status_lcl && msh->spl_cmd[skip])
		status_lcl = parse_cmd_argv(&msh->spl_cmd[skip], 0, msh);
	if (!status_lcl && msh->spl_cmd[skip])
		run_cmd_exec(msh);
	else
		msh->exit_status = status_lcl;
	redir_clean(&rdr);
	ft_free_spl_cmd(msh);
}
