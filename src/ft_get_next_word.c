/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:49:12 by mvorslov          #+#    #+#             */
/*   Updated: 2023/03/27 16:49:38 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

int	wrd_collect(char *line)
{
	int	count;
	int	quo_flag;

	count = 0;
	quo_flag = 0;
	if (line[count] == '$')
		count++;
	while (line[count] && !is_in_str(line[count], STR_WHSPACE)
		&& !is_in_str(line[count], STR_REDIR))
	{
		if (is_in_str(line[count], STR_QUOTE))
		{
			quo_flag = quo_check(line[count], quo_flag);
			while (line[++count] && quo_flag)
				quo_flag = quo_check(line[count], quo_flag);
		}
		else
			count++;
	}
	return (count);
}

char	*get_next_word(char *line, t_msh *msh, int *i)
{
	char	*wrd;
	char	tmp;

	if (!(*line))
		return (NULL);
	*i += wrd_collect(line);
	tmp = line[*i];
	line[*i] = '\0';
	wrd = param_expansion(line, msh, quo_check(*line, 0));
	line[*i] = tmp;
	return (wrd);
}
