/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_fun.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:40:48 by ede-smet          #+#    #+#             */
/*   Updated: 2023/02/01 13:53:02 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_FUN_H
# define MINI_FUN_H
# include "../lib/libft/libft.h"
# include "mini_struct.h"
# include <sys/types.h>
# include <dirent.h>

// Builtins prototypes
int		ft_echo(char *input[]);
int		ft_cd(char **input, t_env *env);
int		ft_pwd(char **env);
int		ft_export(void);
int		ft_unset(void);
int		ft_exit(void);
// Environment functions
int		ft_env(char **env);
void	ft_parent_env_cpy(t_env *env, char **envp);
int		env_edit(t_env *env, char *var, char *value);
char	*env_get(char **env, char *var);

// Generic functions
void	free_table(char **table);

#endif
