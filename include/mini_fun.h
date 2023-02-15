/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_fun.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:40:48 by ede-smet          #+#    #+#             */
/*   Updated: 2023/02/15 17:00:21 by ede-smet         ###   ########.fr       */
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
int		ft_cd(char **input, char ***env);
int		ft_pwd(void);
int		ft_export(char ***env, char **inputs);
int		ft_unset(char ***env, char **inputs);
int		ft_exit(void);
int		ft_env(char **env);
// Environment extra functions
int		env_exist(char **env, char *var);
void	ft_fill_env(char *env, char *var, char *value);
int		ft_count_elem(char **envp);
int		ft_parent_env_cpy(char ***env, char **envp);
int		env_edit(char ***env, char *var, char *value);
char	*env_get(char **env, char *var);
int		env_add(char ***env, char *value);
int		env_del(char ***env, char *var);

// Generic functions
void	free_table(char **table);

#endif
