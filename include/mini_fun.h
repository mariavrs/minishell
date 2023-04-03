/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_fun.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:40:48 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/03 14:32:39 by ede-smet         ###   ########.fr       */
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
int				ft_parent_env_cpy(char ***env, char **envp);
int				env_not_exist(char **env, char *var);
int				env_edit(t_msh *msh, char *var, char *value, int flag);
char			*env_get(char **env, char *var);
int				env_del(char ***env, char *var);
int				pos_sep(char *str);
int				env_size(char **env);

// cd utils
int				fill_env(t_msh *msh, char *path);
char			*current_pwd(t_msh *msh);
int				check_if_pwd_equal_envp(t_msh *msh, char *var);

// Signals
void			signal_manager(int mode);
void			ctrl_c_heredoc_handler(int sig);
void			ctrl_c_heredoc_pipe_handler(int sig);

// Parse & Execute
void			parse_exec_prep(t_msh *msh);
int				syntax_check(char *line, char *eline);

void			parse_list(char *line, char *eline, t_msh *msh);

void			parse_pipe(char *line, char *eline, t_msh *msh);
void			run_pipe(char *line, char *eline, char *del, t_msh *msh);

void			parse_simple_cmd(char *line, char *eline, t_msh *msh);

int				first_wrd_check(int *skip, char *line, t_msh *msh);

int				parse_redir(char *line, int i, t_redir *rdr, t_msh *msh);
int				run_redir(char *line, int *i, t_redir *rdr, t_msh *msh);
int				redir_in(char *filename, t_redir *rdr, t_msh *msh);
int				redir_out(char *filename, t_redir *rdr);
int				redir_heredoc(char *delim, t_redir *rdr, t_msh *msh);
void			redir_clean(t_redir *rdr);
int				heredoc_prep(t_heredoc *hd);
int				heredoc_collect_status(pid_t pid);
int				heredoc_collect(char *delim, t_heredoc *hd,
					t_redir *rdr, t_msh *msh);

int				parse_cmd_argv(char *line, int argc, t_msh *msh);
void			run_cmd_exec(t_msh *msh);

// Parse & Execute Utils
char			*get_next_word(char *line, t_msh *msh, int *i);
int				is_in_str(char c, char *str);
int				brackets_check(char *line, char *eline);
int				trim_brackets(char **line, char **eline);
int				trim_whitespaces(char **line, char **eline);
int				quo_check(char del, int quo_flag);

// Expansion
char			*param_expansion(char *line, t_msh *msh, int quo_flag);
int				get_var_name_len(char *line);
int				is_valid_varname(char c);
int				check_if_varname(char *line, int quo_flag);

// Environment Add/Replace
int				get_full_var_str(char *line, t_env *env, t_msh *msh);
int				find_in_envp(t_env *env, t_msh *msh);
int				get_env_mod(char c);

int				put_env_var(t_env *env, t_msh *msh);
int				env_add(t_env env, t_msh *msh, char **envp, int env_flag);
int				env_replace(t_env env, char **envp);

// General Utils
long long int	ft_ll_atoi(const char *str);
char			*ft_malloc_str(int size);
void			ft_free_spl_cmd(t_msh *msh);
void			ft_free_dbl_str(char ***str);
void			ft_free_str(char **str);
void			ft_free_exit(t_msh *msh);
void			error_unexpected_token(char *str);
void			error_custom_arg(char *arg, char *err_msg);
int				cd_error(char **input, char *home);
void			exp_error(char *var, char *check, int *flag);

#endif
