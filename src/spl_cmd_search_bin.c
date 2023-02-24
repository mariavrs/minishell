/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_search_bin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 23:34:56 by mvorslov          #+#    #+#             */
/*   Updated: 2023/02/24 23:40:53 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

void	run_bin(char *full_name, char **argv, t_msh *msh)
{
	if (fork() == 0)
		execve(full_name, argv, msh->envp);
	else
		wait(&msh->exit_status);
}

char	*bin_get_full_name(char *path, char *argv, int name_len)
{
	int			path_len;
	char		*full_name;
	struct stat	statbuf;

	path_len = ft_strlen(path);
	full_name = malloc(sizeof(char) * (path_len + name_len + 2));
	if (full_name)
	{
		ft_strlcpy(full_name, path, path_len + 1);
		full_name[path_len] = '/';
		ft_strlcpy(&full_name[path_len + 1], argv, name_len + 1);
		if (stat(full_name, &statbuf))
		{
			free(full_name);
			full_name = NULL;
		}
	}
	return (full_name);
}

int	search_in_path(char **argv, t_msh *msh)
{
	t_path	pb;
	int		i;

	i = -1;
	pb.path_val = env_get(msh->envp_lcl, "PATH");
	if (!pb.path_val)
		pb.path_val = env_get(msh->envp, "PATH");
	if (!pb.path_val)
		return (1);
	pb.path_split = ft_split(pb.path_val, ':');
	free(pb.path_val);
	if (!pb.path_split)
		return (ft_putstr_fd("minishell: malloc error \n", 2), 1);
	pb.full_name = NULL;
	pb.name_len = ft_strlen(argv[0]);
	while (pb.path_split[++i] && !pb.full_name)
		pb.full_name = bin_get_full_name(pb.path_split[i], argv[0],
				pb.name_len);
	i = -1;
	while (pb.path_split[++i])
		free(pb.path_split[i]);
	free(pb.path_split);
	if (pb.full_name)
		return (run_bin(pb.full_name, argv, msh), free(pb.full_name), 0);
	return (1);
}

int	search_bin(char **argv, t_msh *msh)
{
	struct stat	statbuf;

	if (ft_strchr(argv[0], '/'))
	{
		if (!stat(argv[0], &statbuf))
			run_bin(argv[0], argv, msh);
		else
			return (1);
	}
	else
		if (search_in_path(argv, msh))
			return (1);
	return (0);
}
