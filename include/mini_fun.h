/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_fun.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:40:48 by ede-smet          #+#    #+#             */
/*   Updated: 2023/02/23 13:35:31 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_FUN_H
# define MINI_FUN_H
# define _GNU_SOURCE
# include "../lib/libft/libft.h"
# include "mini_struct.h"
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <fcntl.h>

// Builtins prototypes
void	ft_echo(void);
void	ft_cd(void);
void	ft_pwd(void);
void	ft_export(void);
void	ft_unset(void);
void	ft_env(void);
void	ft_exit(void);

// Minishell
void	parse_exec_prep(t_msh *msh);
int		syntax_check_prep(char *line, char *eline);

void	parse_list(char *line, char *eline, t_msh *msh);
int		list_delim_locator(char *line, char *eline, char **del);
void	parse_pipe(char *line, char *eline, t_msh *msh);
void	run_pipe(char *line, char *eline, char *del, t_msh *msh);

int		is_in_str(char c, char *str);
int		brackets_check(char *line, char *eline);
int		trim_brackets(char **line, char **eline);
int		trim_whitespaces(char **line, char **eline);
int		quo_check(char del, int quo_flag);

void	parse_simple_cmd(char *line, char *eline, t_msh *msh);

void	run_spl_cmd(t_spl_cmd *cmd, t_msh *msh);
void	run_exec(t_spl_cmd *cmd, t_msh *msh);

int		redir_in(t_spl_cmd *cmd, int i, t_msh *msh);
int		redir_out(t_spl_cmd *cmd, int i);
void	redir_clean(t_spl_cmd *cmd);

int		ft_malloc_spl_cmd(t_spl_cmd *cmd, int argc, int redirc);
void	ft_free_redir_info(t_spl_cmd *cmd);
void	ft_free_argv(t_spl_cmd *cmd);

char	*param_expansion(char *line, t_msh *msh);

#endif
