/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_fun.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:40:48 by ede-smet          #+#    #+#             */
/*   Updated: 2023/01/30 21:16:40 by ede-smet         ###   ########.fr       */
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
int		ft_cd(char **input);
int		ft_pwd(void);
int		ft_export(void);
int		ft_unset(void);
int		ft_exit(void);
// Environment functions
int		ft_env(char **env);
char	**ft_parent_env_cpy(char **envp);

#endif
