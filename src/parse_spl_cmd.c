/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spl_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:49:24 by mvorslov          #+#    #+#             */
/*   Updated: 2023/02/27 15:34:20 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

int	wrd_collect(char *line, int *quo_detected)
{
	int	count;
	int	quo_flag;

	count = 0;
	quo_flag = quo_check(*line, 0);
	if (quo_flag)
	{
		line++;
		*quo_detected = 1;
		quo_flag = quo_check(*(line + count), quo_flag);
		while (*(line + count) && quo_flag)
		{
			count++;
			quo_flag = quo_check(*(line + count), quo_flag);
		}
	}
	else
	{
		while (*(line + count) && !is_in_str(*(line + count), STR_WHSPACE)
			&& !is_in_str(*(line + count), STR_QUOTE)
			&& !is_in_str(*(line + count), STR_REDIR))
			count++;
	}
	return (count);
}

int	parse_cmd_argv(char *line, int argc, t_msh *msh)
{
	int	quo_detected;
	int	eword;

	quo_detected = 0;
	while (is_in_str(*line, STR_WHSPACE))
		line++;
	if (!(*line))
	{
		msh->argv = malloc(sizeof(char *) * (argc + 1));
		if (!msh->argv)
			return (ft_putstr_fd("minishell: malloc error\n", 2), 1);
		msh->argv[argc] = NULL;
	}
	else
	{
		argc++;
		eword = wrd_collect(line, &quo_detected);
		line += quo_detected;
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
	int		quo_detected;
	char	tmp;
	int		status_lcl;

	i_tmp = *i;
	quo_detected = 0;
	*i += wrd_collect(&line[*i], &quo_detected);
	*i += quo_detected;
	tmp = line[*i];
	line[*i] = '\0';
	if (rdr->mode == '>' || rdr->mode == '+')
		status_lcl = redir_out(&line[i_tmp + quo_detected], rdr);
	else
		status_lcl = redir_in(&line[i_tmp + quo_detected], rdr, msh);
	line[*i] = tmp;
	*i += quo_detected;
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
		if (line[i] == '>' && line[i + 1] == '>')
			rdr->mode = '+';
		else if (line[i] == '>')
			rdr->mode = '>';
		else if (line[i] == '<' && line[i + 1] == '<')
			rdr->mode = '-';
		else if (line[i] == '<')
			rdr->mode = '<';
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

	rdr.stdin_cpy = 0;
	rdr.stdout_cpy = 0;
	trim_whitespaces(&line, &eline);
	*eline = '\0';
	msh->spl_cmd = param_expansion(line, msh);
	status_lcl = parse_redir(msh->spl_cmd, &rdr, msh);
	if (!status_lcl)
		status_lcl = parse_cmd_argv(msh->spl_cmd, 0, msh);
	if (!status_lcl)
		run_cmd_exec(msh);
	else
		msh->exit_status = status_lcl;
	redir_clean(&rdr);
	ft_free_spl_cmd(msh);
}
