/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 22:28:07 by ede-smet          #+#    #+#             */
/*   Updated: 2023/01/23 01:30:51 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

int	ft_execute(char *line)
{
	(void)line;
	return(0);
}

int	ft_parse(char *line)
{
	(void)line;
	return (0);
}

int	main(void)
{
	char *line;

	while (1)
	{
		line = readline("minishell $");
		if (ft_strlen(line) != 0)
		{
			add_history(line);
			ft_parse(line);
			ft_execute(line);
		}
		free(line);
	}
	return (0);
}
