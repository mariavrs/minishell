/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 22:28:07 by ede-smet          #+#    #+#             */
/*   Updated: 2023/02/01 09:54:23 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	**env;

	(void)argc;
	env = ft_parent_env_cpy(envp);
	printf("############ Calling of echo ############\n");
	ft_echo(argv);
	printf("############ Calling of pwd ############\n");
	ft_pwd();
	printf("############ Calling of cd ############\n");
	if (ft_cd(argv) == 1)
		printf("Path invalid !\n");
	ft_pwd();
	printf("############ Calling of env ############\n");
	ft_env(env);
	printf("############ Edit de TERM ############\n");
	env_edit(env, "TERM", "HELLO");
	ft_env(env);
	return (0);
}
