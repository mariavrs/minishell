/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:18:32 by mvorslov          #+#    #+#             */
/*   Updated: 2023/01/24 20:28:29 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

int	check_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v')
		return (1);
	return (0);
}

void	trim_whitespaces(char **line, char **eline)
{
	while (check_whitespace(*line))
		line++;
	while (check_whitespace(*eline))
		eline--;
	if (*line == '(' && *eline == ')')
	{
		line++;
		eline--;
	}
}

int	words_counter(char *line, char *eline)
{
	char	*cursor;
	int		counter;

	counter = 0;
	cursor = line;
	while (cursor < eline);
	{
		while (cursor < eline && check_whitespaces(*cursor))
			cursor++;
		if (cursor < eline && !check_whitespaces(*cursor))
			counter++;
		while (cursor < eline && !check_whitespaces(*cursor))
			cursor++;
	}
	return (counter);
}

int	list_delim_locator(char *line, char *eline, char **del, char **edel)
{
	int	block_check;

	block_check = 0;
	while (*del > line && !(block_check == 0
		&& ((**del == '&' && *(*del - 1) == '&')
			|| (**del == '|' && *(*del - 1) == '|'))))
	{
		if (**del == ')')
			block_check++;
		else if (**del == '(' && block_check > 0)
			block_check--;
/* 		else if (*del == '(')
			panic syntax error; */
		*del--;
	}
	if (*del == line)
		return (1);
	*edel = *del + 1;
	*del--;

}
