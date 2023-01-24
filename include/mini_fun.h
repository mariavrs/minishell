/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_fun.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:40:48 by ede-smet          #+#    #+#             */
/*   Updated: 2023/01/24 21:57:20 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_FUN_H
# define MINI_FUN_H
# include "../lib/libft/libft.h"
# include "mini_struct.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

// Builtins prototypes
void	ft_echo(void);
void	ft_cd(void);
void	ft_pwd(void);
void	ft_export(void);
void	ft_unset(void);
void	ft_env(void);
void	ft_exit(void);

// Minishell
t_cmd	*ft_parse(char *line);
t_cmd	*parse_exec(char *line, char *eline);
t_cmd	*parse_redir(char *line, char *eline);
t_cmd	*parse_pipe(char *line, char *eline);
t_cmd	*parse_list(char *line, char *eline);

int		list_delim_locator(char *line, char *eline, char **del, char **edel);
int		words_counter(char *line, char *eline);
void	trim_whitespaces(char **line, char **eline);
int		check_whitespace(char c);

void	ft_exec_tree(t_cmd *cmd, int exit_status);
void	run_exec(t_exec *cmd, int exit_status);
void	run_redir(t_redir *cmd, int exit_status);
void	run_pipe(t_pipe *cmd, int exit_status);
void	run_list(t_lol *cmd, int exit_status);

#endif
