/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_local_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:02:11 by mvorslov          #+#    #+#             */
/*   Updated: 2023/02/28 14:18:38 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

typedef struct s_env_lcl_detect
{
	int		ln;
	int		env_i;
	char	*env_value;
	int		env_vlen;
}	t_envl;

int	env_lcl_replace(char *line, t_envl envl, t_msh *msh)
{
	if (msh->envp_lcl[envl.env_i])
		free(msh->envp_lcl[envl.env_i]);
	line[envl.ln] = '\0';
	msh->envp_lcl[envl.env_i] = ft_strjoin(line, envl.env_value);
	if (!msh->envp_lcl[envl.env_i])
		return (ft_putstr_fd("minishell: malloc error\n", 2), 1);
	return (0);
}

int	env_lcl_add(char *line, t_envl envl, t_msh *msh)
{
	char	**envp_tmp;

	envl.env_i = 0;
	while (msh->envp_lcl[envl.env_i])
		envl.env_i++;
	envp_tmp = malloc(sizeof(char *) * (envl.env_i + 2));
	if (!envp_tmp)
		return (ft_putstr_fd("minishell: malloc error\n", 2), 1);
	envl.env_i = -1;
	while (msh->envp_lcl[++envl.env_i])
		envp_tmp[envl.env_i] = msh->envp_lcl[envl.env_i];
	free (msh->envp_lcl);
	msh->envp_lcl = envp_tmp;
	msh->envp_lcl[envl.env_i] = NULL;
	msh->envp_lcl[envl.env_i + 1] = NULL;
	return (env_lcl_replace(line, envl, msh));
}

char	*get_var_value(char *cursor, int *quo_detected)
{
	char	*str;
	int		symb_count;

	str = NULL;
	symb_count = wrd_collect(cursor, quo_detected);
	str = malloc(sizeof(char) * (symb_count + 1));
	if (!str)
		return (ft_putstr_fd("minishell: malloc error\n", 2), NULL);
	str[symb_count] = '\0';
	if (*quo_detected)
		cursor++;
	while (--symb_count >= 0)
		str[symb_count] = *(cursor + symb_count);
	return (str);
}

int	find_in_envp_lcl(char *line, int ln, t_msh *msh)
{
	int	i;

	i = -1;
	while (msh->envp_lcl[++i])
	{
		if (!ft_strncmp(line, msh->envp_lcl[i], ln))
			return (i);
	}
	return (-1);
}

int	first_wrd_check(int *skip, char *line, t_msh *msh)
{
	t_envl	envl;
	int		quo_detected;

	envl.ln = -1;
	quo_detected = 0;
	while (is_valid_varname(line[++envl.ln]) || line[envl.ln] == '=')
	{
		if (line[envl.ln] == '=')
		{
			envl.env_value = get_var_value(&line[++envl.ln], &quo_detected);
			if (!envl.env_value)
				return (*skip = 0, 1);
			envl.env_vlen = ft_strlen(envl.env_value);
			*skip = envl.ln + envl.env_vlen + (quo_detected * 2);
			if (line[*skip])
				return (free(envl.env_value), 0);
			envl.env_i = find_in_envp_lcl(line, envl.ln, msh);
			if (envl.env_i >= 0 && env_lcl_replace(line, envl, msh))
				return (free(envl.env_value), *skip = 0, 1);
			else if (envl.env_i < 0 && env_lcl_add(line, envl, msh))
				return (free(envl.env_value), *skip = 0, 1);
			return (free(envl.env_value), 0);
		}
	}
	return (0);
}
