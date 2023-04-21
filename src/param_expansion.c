/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:18:59 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/22 01:33:08 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

extern int	g_exit_status;

static int	var_value(char *line, char *str, int *i, t_msh *msh)
{
	int	pos;
	int	ln;

	pos = 0;
	ln = get_var_name_len(line);
	while (msh->envp_lcl[pos] && (ft_strncmp(msh->envp_lcl[pos], line, ln)
			|| msh->envp_lcl[pos][ln] != '='))
		pos++;
	if (!msh->envp_lcl[pos])
	{
		pos = 0;
		while (msh->envp[pos] && (ft_strncmp(msh->envp[pos], line, ln)
				|| msh->envp[pos][ln] != '='))
			pos++;
		if (msh->envp[pos])
			*i += ft_strlcpy(&str[*i], &msh->envp[pos][ln + 1],
					ft_strlen(&msh->envp[pos][ln]));
	}
	else
		*i += ft_strlcpy(&str[*i], &msh->envp_lcl[pos][ln + 1],
				ft_strlen(&msh->envp_lcl[pos][ln]));
	return (ln);
}

static int	var_len(char *line, int *len, t_msh *msh)
{
	int	pos;
	int	ln;

	pos = 0;
	ln = get_var_name_len(line);
	while (msh->envp_lcl[pos] && (ft_strncmp(msh->envp_lcl[pos], line, ln)
			|| msh->envp_lcl[pos][ln] != '='))
		pos++;
	if (!msh->envp_lcl[pos])
	{
		pos = 0;
		while (msh->envp[pos] && (ft_strncmp(msh->envp[pos], line, ln)
				|| msh->envp[pos][ln] != '='))
			pos++;
		if (msh->envp[pos])
			*len += ft_strlen(&msh->envp[pos][ln + 1]);
	}
	else
		*len += ft_strlen(&msh->envp_lcl[pos][ln + 1]);
	return (ln);
}

static int	final_line_len(char *line, t_msh *msh, int quo_flag, int unquote)
{
	int	len;

	len = 0;
	while (*line)
	{
		while (*line && !check_if_varname(line, quo_flag))
		{
			if (!unquote || !((*line == '\'' && quo_flag != 2)
					|| (*line == '\"' && quo_flag != 1)))
				len++;
			quo_flag = quo_check(*(++line), quo_flag);
		}
		if (*line && *(line + 1) == '?')
		{
			len += 3;
			line += 2;
		}
		else if (*line)
			line += var_len(line + 1, &len, msh) + 1;
		quo_flag = quo_check(*line, quo_flag);
	}
	return (len);
}

static int	put_exit_status(char *str, int *i, char **line)
{
	char	*num;
	int		ln;

	num = ft_itoa(g_exit_status);
	if (!num)
		return (malloc_error(), ERR_MALLOC);
	ln = ft_strlen(num);
	ft_strlcpy(str, num, ln + 1);
	ft_free_str(&num);
	*line += 2;
	*i += ln;
	return (0);
}

char	*param_expansion(char *line, t_msh *msh, int quo_flag, int unquote)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_malloc_str(final_line_len(line, msh, quo_flag, unquote) + 1);
	if (!str)
		return (NULL);
	while (*line)
	{
		while (*line && !check_if_varname(line, quo_flag))
		{
			if (!unquote || !((*line == '\'' && quo_flag != 2)
					|| (*line == '\"' && quo_flag != 1)))
				str[i++] = *line;
			quo_flag = quo_check(*(++line), quo_flag);
		}
		if (*line && *(line + 1) == '?' && put_exit_status(&str[i], &i, &line))
			return (ft_free_str(&str), NULL);
		else if (*line && *(line + 1) != '?')
			line += var_value(line + 1, str, &i, msh) + 1;
		quo_flag = quo_check(*line, quo_flag);
	}
	return (str);
}
