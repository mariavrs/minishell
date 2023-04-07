/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:38:32 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/07 16:40:51 by ede-smet         ###   ########.fr       */
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
# include <errno.h>

typedef struct s_spl_cmd
{
	int					fd_in;
	int					fd_out;
	char				rdr_mode;
	char				*spl_cmd;
	char				**argv;
	struct s_spl_cmd	*next;
}	t_cmd;

typedef struct s_block
{
	char			mode;
	t_cmd			*pipeline;
	struct s_block	*next;
}	t_block;

typedef struct s_msh
{
	char	**envp;
	char	**envp_lcl;
	char	*sline;
	char	*ex_sline;
	int		stdin_default;
	int		stdout_default;
	int		malloc_err_parse;
	t_block	*cmd_list;
}	t_msh;

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

#endif
