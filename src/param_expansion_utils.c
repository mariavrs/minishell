/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:28:14 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/03 13:36:53 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

int	check_if_varname(char *line, int quo_flag)
{
	if (*line == '$' && quo_flag != 1
		&& (is_valid_varname(*(line + 1)) || *(line + 1) == '?')
		&& !ft_isdigit(*(line + 1)))
		return (1);
	return (0);
}

int	is_valid_varname(char c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9')
		|| c == '_')
		return (1);
	return (0);
}

int	get_var_name_len(char *line)
{
	int	ln;

	ln = 0;
	while (is_valid_varname(*(line + ln)))
		ln++;
	return (ln);
}
