/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 22:28:07 by ede-smet          #+#    #+#             */
/*   Updated: 2023/01/27 14:16:06 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

int	main(int argc, char *argv[])
{
	(void)argc;
	printf("############ Calling of echo ############\n");
	ft_echo(argv);
	printf("############ Calling of pwd ############\n");
	ft_pwd();
	printf("############ Calling of cd ############\n");
	if (ft_cd(argv) == 1)
		printf("J'encule des mouches !\n");
	ft_pwd();
	return (0);
}
