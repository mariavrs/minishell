/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 23:25:09 by mvorslov          #+#    #+#             */
/*   Updated: 2023/02/10 23:31:09 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

char	*ft_strjoin_custom(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	return (str);
}

void	run_exec_bin(char **argv, int *exit_status, char **envp)
{
	char	*full_fun_name;

	full_fun_name = ft_strjoin_custom("/usr/bin/", *argv);
	if (fork() == 0)
		execve(full_fun_name, argv, envp);
	else
		wait(exit_status);
	free(full_fun_name);
}

int	run_search_bin(char **argv, int *exit_status, char **envp)
{
	DIR	*bin_lib;
	struct dirent *bin_lib_obj;

	bin_lib = NULL;
	bin_lib = opendir("/usr/bin");
/* 	if (!bin_lib)
		panic open didn't work, quit everything */
	bin_lib_obj = readdir(bin_lib);
	while (bin_lib_obj && ft_strncmp(bin_lib_obj->d_name, *argv, ft_strlen(*argv) + 1))
		bin_lib_obj = readdir(bin_lib);
	closedir(bin_lib);
	if (bin_lib_obj) // I'm not sure if we have to check the type
		run_exec_bin(argv, exit_status, envp);
	else
		return (1);
	return (0);
}

void	run_exec(t_spl_cmd *cmd, int *exit_status, char **envp)
{
	if (!ft_strncmp(cmd->argv[0], "cd", 3))
		ft_cd();
	else if (!ft_strncmp(cmd->argv[0], "echo", 5))
		ft_echo();
	else if (!ft_strncmp(cmd->argv[0], "env", 4))
		ft_env();
	else if (!ft_strncmp(cmd->argv[0], "exit", 5))
		ft_exit();
	else if (!ft_strncmp(cmd->argv[0], "export", 7))
		ft_export();
	else if (!ft_strncmp(cmd->argv[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(cmd->argv[0], "unset", 6))
		ft_unset();
	else if (run_search_bin(cmd->argv, exit_status, envp))
	{
		printf("minishell: %s: command not found :(\n", cmd->argv[0]);//modify with strerror or perror
		*exit_status = 127;
	}
}