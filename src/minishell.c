/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 22:28:07 by ede-smet          #+#    #+#             */
/*   Updated: 2023/02/02 12:43:51 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	**env;

	(void)argc;
	ft_parent_env_cpy(&env, envp);
	printf("############ Calling of echo ############\n");
	ft_echo(argv);
	printf("############ Calling of pwd ############\n");
	ft_pwd(env);
	printf("############ Calling of cd ############\n");
	if (ft_cd(argv, &env) == 1)
		printf("Path invalid !\n");
	ft_pwd(env);
	printf("############ Calling of env ############\n");
	ft_env(env);
	printf("############ add var in env ############\n");
	env_add(&env, "NTM=lol");
	ft_env(env);
	return (free_table(env), 0);
}
