/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:18:32 by mvorslov          #+#    #+#             */
/*   Updated: 2023/02/15 19:20:07 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

int	check_if_in_str(char c, char *str)
{
	while (*str)
		if (c == *str++)
			return (1);
	return (0);
}

int	brackets_check(char *line, char *eline)
{
	int		check;
	char	*cursor;

	check = 0;
	cursor = line;
	while (cursor < eline && check >= 0)
	{
		if (*cursor == '(')
			check++;
		else if (*cursor == ')')
			check--;
		cursor++;
	}
	if (!check)
		return (0);
	return (1);
}

int	trim_brackets(char **line, char **eline)
{
	if (*line + 1 < *eline && **line == '(' && *(*eline - 1) == ')' && !brackets_check(*line + 1, *eline - 1))
	{
		*line = *line + 1;
		*eline = *eline - 1;
		if (trim_whitespaces(line, eline))
			return (1);
	}
	if (**line == '(' && *(*eline - 1) == ')')
		return (1);
	return (0);
}

int	trim_whitespaces(char **line, char **eline)
{
	while (*line < *eline && check_whitespace(**line))
		*line = *line + 1;
	while (*eline > *line && check_whitespace(*(*eline - 1)))
		*eline = *eline - 1;
	if (*line == *eline)
		return (1);
	return (0);
}

int	quo_check(char del, int quo_flag)
{
	if (!quo_flag && del == '\'')
		quo_flag = 1;
	else if (!quo_flag && del == '\"')
		quo_flag = 2;
	else if (quo_flag == 1 && del == '\'')
		quo_flag = 0;
	else if (quo_flag == 2 && del == '\"')
		quo_flag = 0;
	return (quo_flag);
}

int	quo_stx_check(char *line, char *eline)
{
	int	flag;

	flag = 0;
	while (line <= eline)
		flag = quo_check(*(line++), flag);
	return(flag);
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
