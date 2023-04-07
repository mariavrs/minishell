/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_fun.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:40:48 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/08 00:27:05 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_FUN_H
# define MINI_FUN_H
# define _GNU_SOURCE
# include "../lib/libft/libft.h"
# include "mini_struct.h"

// Signals
void			signal_manager(int mode);
void			ctrl_c_heredoc_handler(int sig);

// Parse & Execute
int				msh_prep(t_msh *msh, char **envp);
int				syntax_check(char *line, char *eline);
t_block			*parse_list(char *line, char *eline, t_msh *msh, char mode);
t_cmd			*parse_pipe(char *line, char *eline, t_msh *msh);
void			run_pipe(t_msh *msh, t_cmd *cmd);

t_cmd			*parse_simple_cmd(char *line, char *eline, t_msh *msh);
int				first_wrd_check(int *skip, char *line, t_msh *msh);

int				parse_redir(t_msh *msh, t_cmd *cmd, char *line, int i);
int				run_redir(t_cmd *cmd, char *line, int *i, t_msh *msh);
int				redir_in(t_msh *msh, t_cmd *cmd, char *filename);
int				redir_out(t_cmd *cmd, char *filename);
int				redir_heredoc(t_msh *msh, t_cmd *cmd, char *eof);
void			redir_clean(t_msh *msh, t_cmd *cmd);
int				heredoc_prep(t_msh *msh, t_heredoc *hd);
int				heredoc_collect_status(pid_t pid);
int				heredoc_collect(t_msh *msh, t_cmd *cmd,
					t_heredoc *hd, char *eof);
void			heredoc_clean(t_heredoc *hd);

int				parse_cmd_argv(t_msh *msh, t_cmd *cmd, char *line, int argc);
void			run_cmd_exec(t_msh *msh, t_cmd *cmd);

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
void			ft_free_dbl_str(char ***str);
void			ft_free_str(char **str);
void			ft_free_cmd(t_cmd **cmd);
void			ft_free_pipeline(t_cmd **cmd);
void			ft_free_cmd_list_block(t_block	**cmd_block);
void			ft_free_cmd_list(t_block	**cmd_block);
void			ft_free_exit(t_msh *msh);
void			ft_mini_perror(char *s1, char *s2,
					char *err_msg, int print_msh);
void			malloc_error(void);
void			error_unexpected_token(char *str);
int				error_cd(t_msh *msh, char **argv, char *home);
void			error_export(char *var, int *flag);

// Builtins prototypes
int				ft_echo(t_msh *msh, char **argv);
int				ft_cd(t_msh *msh, char **argv);
int				ft_pwd(void);
int				ft_export(t_msh *msh, char **argv);
int				ft_unset(t_msh *msh, char **argv);
int				ft_exit(t_msh *msh, char **argv);
int				ft_env(t_msh *msh, char **argv, int mode);

// env, export, unset: extra functions
int				if_not_exist(t_msh *msh, char *var, int src);
int				env_edit(t_msh *msh, char *var, char *value, int flag);
int				env_remove_line(t_msh *msh, t_env env, char **envp);
int				env_get(char **value, char *name, t_msh *msh);
int				env_del(t_msh *msh, char *var);
int				env_val_start_pos(char *str);
int				dbl_str_size(char **env);

// cd: utils
int				cd_fill_env(t_msh *msh, char *path);
char			*cd_get_value(t_msh *msh, char *var);
int				check_if_pwd_equal_envp(t_msh *msh, char *var);

#endif
