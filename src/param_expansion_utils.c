/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:28:14 by mvorslov          #+#    #+#             */
/*   Updated: 2023/02/25 15:28:35 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

int	get_var_name_len(char *line)
{
	int	ln;

	ln = 0;
	while (*(line + ln) && *(line + ln) != '$' && *(line + ln) != '?'
		&& !is_in_str(*(line + ln), STR_QUOTE)
		&& !is_in_str(*(line + ln), STR_WHSPACE)
		&& !is_in_str(*(line + ln), STR_REDIR))
		ln++;
	return (0);
}
