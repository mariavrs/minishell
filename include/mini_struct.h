/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:38:32 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/02 20:12:32 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_STRUCT_H
# define MINI_STRUCT_H

# define STR_WHSPACE " \t\n\r\v"
# define STR_REDIR "<>"
# define STR_QUOTE "\'\""
# define STR_BRACKETS "()"
# define STR_LOL "|&"
# define STR_SPECIAL " \t\n\r\v<>()\'\"|&"

# define ENV_LCL 0
# define ENV_EXP 1
# define ENV_REPLC 0
# define ENV_APPEND 1
# define ENV_EXPND -1
# define MODE_NITR 0
# define MODE_INTR_CMD 1
# define MODE_INTR_HDC 2

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/types.h>
# include <stdlib.h>

typedef struct s_msh
{
	char	**envp;
	char	**envp_lcl;
	char	*sline;
	char	*ex_sline;
	char	*spl_cmd;
	int		spl_cmd_len;
	char	**argv;
	int		stdin_default;
	int		stdout_default;
	int		in_pipe_flag;
	int		out_pipe_flag;
}	t_msh;

typedef struct s_stx
{
	char	special_ch;
	int		quo_flag;
	int		brackets_flag;
}	t_stx;

typedef struct s_redir
{
	int		stdin_cpy;
	int		stdout_cpy;
	int		fd;
	char	mode;
}	t_redir;

typedef struct s_heredoc
{
	char		*line_in;
	char		*line_out;
	char		*hdoc;
	char		*hdoc_id;
	int			status;
	struct stat	statbuf;
}	t_heredoc;

typedef struct s_env
{
	char	*full_var;
	char	*name;
	char	*value;
	int		full_var_ln;
	int		name_ln;
	int		value_ln;
	int		src;
	int		dest;
	int		i;
	int		mod;
}	t_env;

typedef struct s_search_bin
{
	char	**path_split;
	char	*path_val;
	char	*full_name;
	int		name_len;
}	t_path;

#endif
