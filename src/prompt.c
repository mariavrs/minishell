/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:16:41 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/11 23:56:54 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_fun.h"

static int	get_last_pos_slash(char *path)
{
	int	lenght;

	if (!path)
		return (0);
	lenght = ft_strlen(path);
	while (lenght > 0)
	{
		if (path[lenght] == '/')
			return (lenght);
		lenght--;
	}
	return (0);
}

static void	get_current_folder(char **folder, t_msh *msh)
{
	char	current_path[PATH_MAX];
	int		slash_pos;

	*folder = NULL;
	if (!getcwd(current_path, PATH_MAX))
	{
		perror("getcwd: ");
		ft_putendl_fd("exit", 1);
		ft_free_exit(msh);
		exit(ERR_MALLOC);
	}
	slash_pos = get_last_pos_slash(current_path);
	if (slash_pos == 0)
		*folder = ft_strjoin("/", current_path + slash_pos + 1);
	else
		*folder = ft_strjoin("../", current_path + slash_pos + 1);
	if (!*folder)
	{
		ft_putendl_fd("minishell: malloc error", 2);
		ft_putendl_fd("exit", 1);
		ft_free_exit(msh);
		exit(ERR_MALLOC);
	}
}

static char	*concat_str(char *s1, char *s2, char *s3)
{
	int		size;
	char	*result;

	if (!s2)
		return ("\033[36;1mminishell:\033[90;1m../.\033[33;1m ~ \033[0m");
	size = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	result = ft_malloc_str(size + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, ft_strlen(s1) + 1);
	ft_strlcpy(result + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	ft_strlcpy(result + ft_strlen(s1) + ft_strlen(s2), s3, ft_strlen(s3) + 1);
	return (result);
}

void	get_prompt(char **prompt, t_msh *msh)
{
	char	*folder;

	folder = NULL;
	if (*prompt)
		ft_free_str(prompt);
	get_current_folder(&folder, msh);
	*prompt = concat_str("\033[36;1mminishell:\033[90;1m", folder,
			"\033[33;1m ~ \033[0m");
	if (!*prompt)
	{
		ft_free_str(&folder);
		ft_putendl_fd("minishell: malloc error", 2);
		ft_putendl_fd("exit", 1);
		ft_free_exit(msh);
		exit(ERR_MALLOC);
	}
	ft_free_str(&folder);
}
