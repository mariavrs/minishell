/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spl_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:49:24 by mvorslov          #+#    #+#             */
/*   Updated: 2023/02/22 16:49:48 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

int	redir_info(char *line, char *mode)
{
	int		count;

	count = 1;
	if (*line != *(line + 1))
		*mode = *line;
	else if (*line == '<')
		*mode = '-';
	else
		*mode = '+';
	if (*line == *(line + 1))
		count++;
	while (*(line + count) && is_in_str(*(line + count), STR_WHSPACE))
		count++;
	return (count);
}

int	wrd_collect(char *line, int *env_flag)
{
	int	count;
	int	quo_flag;

	count = 0;
	*env_flag = 0;
	quo_flag = quo_check(*line, 0);
	if (quo_flag)
	{
		while (*(line + count) && quo_flag)
		{
			if (*(line + count) == '$' && quo_flag != 1)
				*env_flag = 1;
			count++;
			quo_flag = quo_check(*(line + count), quo_flag);
		}
	}
	else
	{
		while (*(line + count) && !is_in_str(*(line + count), STR_WHSPACE)
			&& !is_in_str(*(line + count), STR_QUOTE) && !is_in_str(*(line + count), STR_REDIR))
		{
			if (*(line + count) == '$')
				*env_flag = 1;
			count++;
		}
	}
	return (count);
}

char	*env_join_str(char *line, int symb_count)
{
	char	*str;

//	THIS FUN WILL BE DEVELOPED LATER (for now it's just a copy of the general one)
	str = malloc(sizeof(char) * (symb_count));
	str[symb_count] = '\0';
	while (--symb_count >= 0)
		str[symb_count] = *(line + symb_count);
	return (str);
}

int	fill_the_struct(t_spl_cmd *cmd, char *line, int argc, int redirc, int symb_count, char mode, int env_flag)
{
	char	*str;

	if (!env_flag)
	{
		str = malloc(sizeof(char) * (symb_count + 1));
		str[symb_count] = '\0';
		while (--symb_count >= 0)
			str[symb_count] = *(line + symb_count);
	}
	else
		str = env_join_str(line, symb_count);
	if (mode)
	{
		cmd->redir[redirc - 1].file = str;
		cmd->redir[redirc - 1].mode = mode;
	}
	else
		cmd->argv[argc - 1] = str;
	return (0);
}

int	build_the_struct(t_spl_cmd *cmd, char *line, int argc, int redirc)
{
	int		symb_count;
	char	mode;
	int		env_flag;

	symb_count = 0;
	mode = '\0';
	while (line && is_in_str(*line, STR_WHSPACE))
		line++;
	if (!(*line))
		return (ft_malloc_spl_cmd(cmd, argc, redirc));
	if (is_in_str(*line, STR_REDIR))
	{
		line += redir_info(line, &mode);
		redirc++;
	}
	else
		argc++;
	symb_count = wrd_collect(line, &env_flag);
	if (build_the_struct(cmd, line + symb_count, argc, redirc))
		return (1);
	return (fill_the_struct(cmd, line, argc, redirc, symb_count, mode, env_flag));
}

void	parse_simple_cmd(char *line, char *eline, t_msh *msh)
{
	t_spl_cmd	cmd;

	trim_whitespaces(&line, &eline);
	*eline = '\0';
	if (build_the_struct(&cmd, line, 0, 0))
		return ;
	cmd.stdin_cpy = 0;
	cmd.stdout_cpy = 0;
	run_spl_cmd(&cmd, msh);
}
