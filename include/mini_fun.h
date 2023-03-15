/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_fun.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:40:48 by ede-smet          #+#    #+#             */
/*   Updated: 2023/03/15 00:31:38 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_FUN_H
# define MINI_FUN_H
# define _GNU_SOURCE
# include "../lib/libft/libft.h"
# include "mini_struct.h"

// Builtins prototypes
int				ft_echo(char *input[]);
int				ft_cd(char **input, t_msh *msh);
int				ft_pwd(void);
int				ft_export(t_msh *msh, char **inputs);
int				ft_unset(t_msh *msh, char **inputs);
int				ft_exit(char **input, t_msh *msh);
int				ft_env(t_msh msh, int mode);
// Environment extra functions
int				env_exist(char **env, char *var);
void			ft_fill_env(char *env, char *var, char *value);
int				ft_count_elem(char **envp);
int				ft_parent_env_cpy(char ***env, char **envp);
int				env_edit(char ***env, char *var, char *value);
char			*env_get(char **env, char *var);
int				env_del(char ***env, char *var);
int				pos_sep(char *str);
int				env_size(char **env);

// utils functions
long long int	ft_ll_atoi(const char *str);

// Minishell
void			parse_exec_prep(t_msh *msh);
int				syntax_check_prep(char *line, char *eline);

void			parse_list(char *line, char *eline, t_msh *msh);
int				list_delim_locator(char *line, char *eline, char **del);
void			parse_pipe(char *line, char *eline, t_msh *msh);
void			run_pipe(char *line, char *eline, char *del, t_msh *msh);

int				is_in_str(char c, char *str);
int				brackets_check(char *line, char *eline);
int				trim_brackets(char **line, char **eline);
int				trim_whitespaces(char **line, char **eline);
int				quo_check(char del, int quo_flag);

void			close_fd(int fd0, int fd1);
void			run_pipe_left(int fd[2], char *line, char *del, t_msh *msh);
void			run_pipe_right(int fd[2], char *eline, char *del, t_msh *msh);

void			parse_simple_cmd(char *line, char *eline, t_msh *msh);
int				wrd_collect(char *line, int count);

void			run_cmd_exec(t_msh *msh);
int				search_bin(char **argv, t_msh *msh);

int				redir_in(char *filename, t_redir *rdr, t_msh *msh);
int				redir_out(char *filename, t_redir *rdr);
void			redir_clean(t_redir *rdr);

char			*param_expansion(char *line, t_msh *msh);
int				get_var_name_len(char *line);
int				is_valid_varname(char c);

int				first_wrd_check(int *skip, char *line, t_msh *msh);

int				find_in_envp(t_env env, char **envp);
int				env_lcl_add(t_env env, t_msh *msh, char **envp, int env_flag);
int				env_lcl_replace(t_env env, char **envp);

void			ft_free_spl_cmd(t_msh *msh);
void			ft_free_dbl_str(char ***str);
void			ft_free_str(char **str);
void			ft_free_exit(t_msh *msh);

#endif
