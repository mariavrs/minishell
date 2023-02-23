/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 22:28:07 by ede-smet          #+#    #+#             */
/*   Updated: 2023/02/23 16:28:11 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_msh	msh;

	(void)argc;
	ft_parent_env_cpy(&(msh.envp), envp);
	printf("############ Calling of echo ############\n");
	ft_echo(argv);
	printf("############ Calling of pwd ############\n");
	ft_pwd();
	printf("############ Calling of env ############\n");
	ft_env(msh);
	printf("############ Calling of cd ############\n");
	env_del(&(msh.envp), "PWD");
	env_del(&(msh.envp), "PWD");
	env_del(&(msh.envp), "OLDPWD");
	env_del(&(msh.envp), "HOME");
	ft_cd(argv, &(msh.envp));
	ft_pwd();
	printf("############ Calling of env ############\n");
	ft_env(msh);
	printf("############ add NTM in env ############\n");
	env_add(&msh.envp, "NTM=lol");
	ft_env(msh);
	printf("############ del LOGNAME from env ############\n");
	env_del(&(msh.envp), "LOGNAME");
	ft_env(msh);
	printf("############ Calling of export ############\n");
	ft_export(&msh, argv);
	ft_env(msh);
	printf("############ Calling of unset ############\n");
	ft_unset(&msh, argv);
	ft_env(msh);
	return (free_table(msh.envp), 0);
}
