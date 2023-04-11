/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:49:12 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/10 21:09:22 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

char	*get_next_word(char *src, int *src_i, int dest_i, int quo_flag)
{
	char	*dest;
	char	c;

	while ((src[*src_i] == '\"' && quo_flag != 1)
		|| (src[*src_i] == '\'' && quo_flag != 2))
		quo_flag = quo_check(src[++(*src_i)], quo_flag);
	if (src[*src_i] && (!is_in_str(src[*src_i], STR_WHSPACE) || quo_flag))
	{
		c = src[(*src_i)++];
		dest = get_next_word(src, src_i, dest_i + 1, quo_flag);
		if (!dest)
			return (NULL);
		dest[dest_i] = c;
	}
	else
	{
		dest = NULL;
		dest = malloc(sizeof(char) * (dest_i + 1));
		if (!dest)
			return (malloc_error(), NULL);
		dest[dest_i] = '\0';
	}
	return (dest);
}
