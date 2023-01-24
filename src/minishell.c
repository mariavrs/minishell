/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 22:28:07 by ede-smet          #+#    #+#             */
/*   Updated: 2023/01/24 01:15:50 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

int	ft_exec_tree(t_cmd *cmd)
{
	(void)cmd;
	return (0);
}

t_cmd	*ft_parse(char *line)
{
	t_cmd	*ret;
	char	*eline;

	eline = line + ft_strlen(line);
	return (ret);
}

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("\033[1;36mminishell>>> \033[0m");
		if (ft_strlen(line) != 0)
		{
			add_history(line);
			ft_exec_tree(ft_parse(line));
		}
		free(line);
	}
	return (0);
}
