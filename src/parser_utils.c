/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:18:32 by mvorslov          #+#    #+#             */
/*   Updated: 2023/01/25 19:07:38 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

int	check_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v')
		return (1);
	return (0);
}

int	brackets_check(char *line, char *eline)
{
	int		check;
	char	*cursor;

	check = 0;
	cursor = line;
	while (cursor <= eline && check >= 0)
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
	while (*line + 1 < *eline && **line == '(' && **eline == ')' && !brackets_check(*line + 1, *eline - 1))
	{
		*line = *line + 1;
		*eline = *eline - 1;
		if (trim_whitespaces(line, eline))
			return (1);
	}
	if (**line == '(' && **eline == ')')
		return (1);
	return (0);
}

int	trim_whitespaces(char **line, char **eline)
{
	while (*line < *eline && check_whitespace(**line))
		*line = *line + 1;
	while (*eline >= *line && check_whitespace(**eline))
		*eline = *eline - 1;
	if (*line > *eline)
		return (1);
	return (0);
}

int	words_counter(char *line, char *eline)
{
	char	*cursor;
	int		counter;

	counter = 0;
	cursor = line;
	while (cursor <= eline)
	{
		while (cursor <= eline && check_whitespace(*cursor))
			cursor++;
		if (cursor <= eline && !check_whitespace(*cursor))
			counter++;
		while (cursor <= eline && !check_whitespace(*cursor))
			cursor++;
	}
	return (counter);
}

int	list_delim_locator(char *line, char *eline, char **del)
{
	int	block_check;

	block_check = 0;
	*del = eline;
	while (*del > line && !(block_check == 0
		&& ((**del == '&' && *(*del - 1) == '&')
			|| (**del == '|' && *(*del - 1) == '|'))))
	{
		if (**del == ')')
			block_check++;
		else if (**del == '(')
			block_check--;
		*del = *del - 1;
	}
	if (*del == line)
		return (1);
	*del = *del - 1;
	return (0);
}
