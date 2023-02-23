/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spl_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:49:24 by mvorslov          #+#    #+#             */
/*   Updated: 2023/02/23 01:19:12 by mvorslov         ###   ########.fr       */
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

int	wrd_collect(char *line, t_cmd_bld *bld)
{
	int	count;
	int	quo_flag;

	count = 0;
	bld->env_flag = 0;
	quo_flag = quo_check(*line, 0);
	if (quo_flag)
	{
		line++;
		bld->quote = 1;
		quo_flag = quo_check(*(line + count), quo_flag);
		while (*(line + count) && quo_flag)
		{
			if (*(line + count) == '$' && quo_flag != 1)
				bld->env_flag = 1;
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
				bld->env_flag = 1;
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

int	fill_the_struct(t_spl_cmd *cmd, int argc, int redirc, t_cmd_bld	bld)
{
	char	*str;

	if (!bld.env_flag)
	{
		str = malloc(sizeof(char) * (bld.symb_count + 1));
		str[bld.symb_count] = '\0';
		while (--bld.symb_count >= 0)
			str[bld.symb_count] = *(bld.line + bld.symb_count);
	}
	else
		str = env_join_str(bld.line, bld.symb_count);
	if (bld.mode)
	{
		cmd->redir[redirc - 1].file = str;
		cmd->redir[redirc - 1].mode = bld.mode;
	}
	else
		cmd->argv[argc - 1] = str;
	return (0);
}

int	build_the_struct(t_spl_cmd *cmd, char *line, int argc, int redirc)
{
	t_cmd_bld	bld;

	bld.symb_count = 0;
	bld.mode = '\0';
	bld.quote = 0;
	while (line && is_in_str(*line, STR_WHSPACE))
		line++;
	if (!(*line))
		return (ft_malloc_spl_cmd(cmd, argc, redirc));
	if (is_in_str(*line, STR_REDIR))
	{
		line += redir_info(line, &bld.mode);
		redirc++;
	}
	else
		argc++;
	bld.symb_count = wrd_collect(line, &bld);
	line += bld.quote;
	if (build_the_struct(cmd, line + bld.symb_count + bld.quote, argc, redirc))
		return (1);
	bld.line = line;
	return (fill_the_struct(cmd, argc, redirc, bld));
}

void	parse_simple_cmd(char *line, char *eline, t_msh *msh)
{
	t_spl_cmd	cmd;

	trim_whitespaces(&line, &eline);
	*eline = '\0';
//	line = first_wrd_check(line, msh);
	line = param_expansion(line, msh);
	if (build_the_struct(&cmd, line, 0, 0))
		return ;
	cmd.stdin_cpy = 0;
	cmd.stdout_cpy = 0;
	run_spl_cmd(&cmd, msh);
}

/* void	replace_with_value(char)
{

}

void	save_to_local_env(char *var, char *str, t_msh *msh)
{
	//check if var already exist
	//delete if exist
	//add concat of var+'='+str
}

char	*get_var_value(char *cursor, t_cmd_bld *bld)
{
	char	*str;

	str = NULL;
	bld->symb_count = 0;
	bld->quote = 0;
	bld->symb_count = wrd_collect(cursor, bld);
	str = malloc(sizeof(char) * (bld->symb_count + 1));////
	str[bld->symb_count] = '\0';
	if (bld->quote)
		cursor++;
	while (--bld->symb_count >= 0)
		str[bld->symb_count] = *(cursor + bld->symb_count);
	return (str);
}

int	first_wrd_check(char *line, t_msh *msh)
{
	char	*cursor;
	char	*str;
	t_cmd_bld	bld;

	cursor = line;
	while (*cursor && !is_in_str(*cursor, STR_QUOTE)
		&& !is_in_str(*cursor, STR_WHSPACE)
			&& !is_in_str(*cursor, STR_REDIR))
	{
		if (*cursor == '=')
		{
			*cursor = '\0';
			str = get_var_value(++cursor, &bld);
			save_to_local_env(line, str, msh);
			return (cursor + ft_strlen(str) + (bld.quote * 2));
		}
		cursor++;
	}
	return (line);
}
 */