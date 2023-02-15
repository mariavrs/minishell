/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 22:28:07 by ede-smet          #+#    #+#             */
/*   Updated: 2023/02/15 16:51:28 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	**env;

	(void)argc;
	ft_parent_env_cpy(&env, envp);
/* 	printf("############ Calling of echo ############\n");
	ft_echo(argv);
	printf("############ Calling of pwd ############\n");
	ft_pwd();
	printf("############ Calling of env ############\n");
	ft_env(env);
	printf("############ Calling of cd ############\n");
	env_del(&env, "PWD");
	env_del(&env, "PWD");
	env_del(&env, "OLDPWD");
	env_del(&env, "HOME");
	ft_cd(argv, &env);
	ft_pwd();
	printf("############ Calling of env ############\n");
	ft_env(env);
	printf("############ add NTM in env ############\n");
	env_add(&env, "NTM=lol");
	ft_env(env);
	printf("############ del TERM from env ############\n");
	env_del(&env, "TERM");
	ft_env(env); */
	printf("############ Calling of export ############\n");
	ft_unset(&env, argv);
	ft_env(env);/* 
	printf("############ Calling of unset ############\n");
	ft_unset(&env, argv);
	ft_env(env); */
	return (free_table(env), 0);
}
