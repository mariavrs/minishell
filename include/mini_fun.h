/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_fun.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 23:40:48 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/14 14:23:50 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_FUN_H
# define MINI_FUN_H
# define _GNU_SOURCE
# include "../lib/libft/libft.h"
# include "mini_struct.h"

// Main
int				msh_prep(t_msh *msh, char **envp);
int				syntax_check(char *line, char *eline);

// Signals
void			signal_manager(int mode);
void			ctrl_c_heredoc_handler(int sig);

// Parsing
t_block			*parse_list(char *line, char *eline, t_msh *msh, char mode);
t_cmd			*parse_pipe(char *line, char *eline, t_msh *msh);
t_cmd			*parse_simple_cmd(char *line, char *eline, t_msh *msh);
t_redir			*parse_redir(t_msh *msh, t_cmd *cmd, int i, int quo_flag);
int				redir_heredoc(t_msh *msh, t_redir *rdr);
int				var_declar_fraction_ln(char *line);
int				lcl_var_declaration(t_msh *msh, char *line);
int				parse_cmd_argv(t_cmd *cmd, char *line, int argc);

// Execution
void			run_pipe(t_msh *msh, t_cmd *cmd);
int				run_redir(t_msh *msh, t_cmd *cmd);
void			get_backup_stdio(t_msh *msh, t_cmd *cmd);
void			run_cmd_exec(t_msh *msh, t_cmd *cmd);
void			put_backup_stdio(t_msh *msh, t_cmd *cmd);

// Parsing & Execution Utils
char			*get_next_word(char *src, int *src_i, int dest_i, int quo_flag);
int				is_in_str(char c, char *str);
int				brackets_check(char *line, char *eline);
int				trim_brackets(char **line, char **eline);
int				trim_whitespaces(char **line, char **eline);
int				quo_check(char del, int quo_flag);

// Expansion
char			*param_expansion(char *line, t_msh *msh,
					int quo_flag, int unquote);
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
char			**ft_malloc_dbl_str(int size);
void			ft_free_dbl_str(char ***str);
void			ft_free_str(char **str);
void			ft_free_cmd(t_cmd **cmd);
void			ft_free_redir(t_redir **rdr);
void			ft_free_cmd_list(t_block **cmd_block);
void			ft_free_cmd_elem(t_cmd **cmd);
void			ft_free_redir_elem(t_redir **rdr);
void			ft_free_cmd_list_elem(t_block **cmd_block);
void			ft_free_exit(t_msh *msh);
void			ft_mini_perror(char *s1, char *s2,
					char *err_msg, int print_msh);
void			malloc_error(void);
void			error_unexpected_token(char *str);
int				error_cd(t_msh *msh, char **argv, char *home);
void			error_export(char *var, int *flag);
void			get_prompt(char **prompt, t_msh *msh);
int				waitpid_collect_status(pid_t pid);
char			*cmd_error_msg(char *s1, char *s2, char *err_msg, t_msh *msh);

// Builtins prototypes
int				ft_echo(t_msh *msh, char **argv);
int				ft_cd(t_msh *msh, char **argv);
int				ft_pwd(t_msh *msh);
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
void			ft_exit_error(int exit_flag, char *str, t_msh *msh, int code);

// cd: utils
int				cd_fill_env(t_msh *msh, char *path, char **home);
char			*cd_get_value(t_msh *msh, char *var);
int				check_if_pwd_equal_envp(t_msh *msh, char *var);
int				build_pwd(char *current_dir, t_msh *msh, char *argv);

#endif
