/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:18:59 by mvorslov          #+#    #+#             */
/*   Updated: 2023/02/23 13:33:09 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

int		var_value(char *line, char *str, int *i, t_msh *msh)
{
	int	pos;
	int	ln;

	ln = 0;
	pos = 0;
	while (*(line + ln) && *(line + ln)!= '$' && !is_in_str(*(line + ln), STR_QUOTE)
		&& !is_in_str(*(line + ln), STR_WHSPACE)
			&& !is_in_str(*(line + ln), STR_REDIR))
		ln++;
	while (msh->envp_lcl[pos] && (ft_strncmp(msh->envp_lcl[pos], line, ln) || msh->envp_lcl[pos][ln] != '='))
		pos++;
	if (!msh->envp_lcl[pos])
	{
		pos = 0;
		while (msh->envp[pos] && (ft_strncmp(msh->envp[pos], line, ln) || msh->envp[pos][ln] != '='))
		{
			pos++;
		}
		if (msh->envp[pos])
		{
			ft_strlcpy(&str[*i], &msh->envp[pos][ln + 1], ft_strlen(&msh->envp[pos][ln]));
			*i += ft_strlen(&msh->envp[pos][ln + 1]);
		}
	}
	else
	{
		ft_strlcpy(&str[*i], &msh->envp_lcl[pos][ln + 1], ft_strlen(&msh->envp_lcl[pos][ln]));
		*i += ft_strlen(&msh->envp_lcl[pos][ln + 1]);
	}
	return (ln);
}

int		var_len(char *line, int *len, t_msh *msh)
{
	int	pos;
	int	ln;

	ln = 0;
	pos = 0;
	while (*(line + ln) && *(line + ln)!= '$' && !is_in_str(*(line + ln), STR_QUOTE)
		&& !is_in_str(*(line + ln), STR_WHSPACE)
			&& !is_in_str(*(line + ln), STR_REDIR))
		ln++;
	*len -= ln;
	while (msh->envp_lcl[pos] && (ft_strncmp(msh->envp_lcl[pos], line, ln) || msh->envp_lcl[pos][ln] != '='))
		pos++;
	if (!msh->envp_lcl[pos])
	{
		pos = 0;
		while (msh->envp[pos] && (ft_strncmp(msh->envp[pos], line, ln) || msh->envp[pos][ln] != '='))
			pos++;
		if (msh->envp[pos])
			*len += ft_strlen(&msh->envp[pos][ln + 1]);
	}
	else
		*len += ft_strlen(&msh->envp_lcl[pos][ln + 1]);
	return (ln);
}

int		final_line_len(char *line, t_msh *msh)
{
	int	len;
	int	quo_flag;

	len = ft_strlen(line);
	quo_flag = quo_check(*line, 0);
	while (*line)
	{
		while (*line && !(*line == '$' && quo_flag != 1))
			quo_flag = quo_check(*(line++), quo_flag);
		if (*line)
		{
			line++;
			len--;
			line += var_len(line, &len, msh);
			quo_flag = quo_check(*line, quo_flag);
		}
	}
	return (len);
}

char	*param_expansion(char *line, t_msh *msh)
{
	char	*str;
	int		i;
	int		quo_flag;

	i = 0;
	str = NULL;
	str = malloc(sizeof(char) * (final_line_len(line, msh) + 1));
	if (!str)
		return (write(2, "minishell: malloc error\n", 24), NULL);
	quo_flag = quo_check(*line, 0);
	while (*line)
	{
		while (*line && !(*line == '$' && quo_flag != 1))
		{
			str[i++] = *line;
			quo_flag = quo_check(*(line++), quo_flag);
		}
		if (*line)
		{
			line++;
			line += var_value(line, str, &i, msh);
			quo_flag = quo_check(*line, quo_flag);
		}
	}
	str[i] = '\0';
	return (str);
}
