/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 22:28:07 by ede-smet          #+#    #+#             */
/*   Updated: 2023/02/02 10:28:43 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_env	env;

	(void)argc;
	ft_parent_env_cpy(&env, envp);
	printf("############ Calling of echo ############\n");
	ft_echo(argv);
	printf("############ Calling of pwd ############\n");
	ft_pwd(env.env_cp);
	printf("############ Calling of cd ############\n");
	if (ft_cd(argv, &env) == 1)
		printf("Path invalid !\n");
	ft_pwd(env.env_cp);
	printf("############ Calling of env ############\n");
	ft_env(env.env_cp);
	free_table(env.env_cp);
	return (0);
}
