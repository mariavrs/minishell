/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:28:14 by mvorslov          #+#    #+#             */
/*   Updated: 2023/02/25 16:09:57 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

int	get_var_name_len(char *line)
{
	int	ln;

	ln = 0;
	while ((*(line + ln) >= 'a' && *(line + ln) <= 'z')
		|| (*(line + ln) >= 'A' && *(line + ln) <= 'Z')
		|| (*(line + ln) >= '0' && *(line + ln) <= '9')
		|| *(line + ln) == '_')
		ln++;
	return (ln);
}
