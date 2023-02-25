/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_local_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:02:11 by mvorslov          #+#    #+#             */
/*   Updated: 2023/02/25 15:53:11 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

void	save_to_local_env(char *var, char *str, t_msh *msh)
{
	//check if var already exist
	//delete if exist
	//add concat of var+'='+str
}

char	*get_var_value(char *cursor, t_cmd_bld *bld)
{
	char	*str;

	str = NULL;
	bld->symb_count = 0;
	bld->quote = 0;
	bld->symb_count = wrd_collect(cursor, bld);
	str = malloc(sizeof(char) * (bld->symb_count + 1));////
	str[bld->symb_count] = '\0';
	if (bld->quote)
		cursor++;
	while (--bld->symb_count >= 0)
		str[bld->symb_count] = *(cursor + bld->symb_count);
	return (str);
}

int	first_wrd_check(char *line, t_msh *msh)
{
	char		*cursor;
	char		*str;
	t_cmd_bld	bld;

	cursor = line;
	while (*cursor
		&& !is_in_str(*cursor, STR_QUOTE)
		&& !is_in_str(*cursor, STR_WHSPACE)
		&& !is_in_str(*cursor, STR_REDIR))
	{
		if (*cursor == '=')
		{
			*cursor = '\0';
			str = get_var_value(++cursor, &bld);
			save_to_local_env(line, str, msh);
			return (cursor + ft_strlen(str) + (bld.quote * 2));
		}
		cursor++;
	}
	return (line);
}
