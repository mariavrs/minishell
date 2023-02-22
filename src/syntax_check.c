/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 18:09:04 by mvorslov          #+#    #+#             */
/*   Updated: 2023/02/22 17:17:01 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

void	puterror_unexpected_token(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (*str == '\n')
		write(2, "newline", 7);
	else
	{
		write(2, str++, 1);
		if (*str == *(str - 1))
			write(2, str, 1);
	}
	write(2, "\'\n", 2);
}

int	stx_list_brackets_check(t_stx *stx, char **line)
{
	if (**line == '(')
	{
		if (stx->special_ch && stx->special_ch != '&')
			return (puterror_unexpected_token(*line), 1);
		stx->brackets_flag++;
		stx->special_ch = '(';
	}
	else if (**line == ')')
	{
		if (stx->special_ch == '(' || stx->brackets_flag == 0)
			return (puterror_unexpected_token(*line), 1);
		stx->brackets_flag--;
		stx->special_ch = ')';
	}
	else
	{
		if (stx->special_ch != 'a' && stx->special_ch != ')')
			return (puterror_unexpected_token(*line), 1);
		stx->special_ch = '&';
		*line += 1;
	}
	*line += 1;
	return (0);
}

int	stx_pipe_redir_check(t_stx *stx, char **line)
{
	if (**line == '|')
	{
		if (stx->special_ch != 'a')
			return (puterror_unexpected_token(*line), 1);
		stx->special_ch = '|';
	}
	else if (is_in_str(**line, STR_REDIR))
	{
		if (stx->special_ch == ')' || stx->special_ch == '>')
			return (puterror_unexpected_token(*line), 1);
		stx->special_ch = '>';
	}
	*line += 1;
	if (**line == *(*line - 1))
		*line += 1;
	return (0);
}

int	syntax_check(t_stx stx, char *line, char *eline)
{
	while (line < eline)
	{
		if (is_in_str(*line, STR_WHSPACE))
			while (is_in_str(*line, STR_WHSPACE))
				line++;
		else if ((!ft_strncmp(line, "&&", 2) || !ft_strncmp(line, "||", 2)
				|| is_in_str(*line, STR_BRACKETS)) && !stx.quo_flag)
		{
			if (stx_list_brackets_check(&stx, &line))
				return (1);
		}
		else if ((is_in_str(*line, STR_REDIR) || *line == '|') && !stx.quo_flag)
		{
			if (stx_pipe_redir_check(&stx, &line))
				return (1);
		}
		else
		{
			stx.quo_flag = quo_check(*(line++), stx.quo_flag);
			stx.special_ch = 'a';
		}
	}
	if (stx.quo_flag || stx.brackets_flag > 0
		|| (stx.special_ch != 'a' && stx.special_ch != ')'))
		return (puterror_unexpected_token("\n"), 1);
	return (0);
}

int	syntax_check_prep(char *line, char *eline)
{
	t_stx	stx;

	stx.special_ch = '\0';
	stx.quo_flag = 0;
	stx.brackets_flag = 0;
	return (syntax_check(stx, line, eline));
}
