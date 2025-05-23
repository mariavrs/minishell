/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:38:32 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/18 16:13:58 by mvorslov         ###   ########.fr       */
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
# define RDR_WCREAT 0
# define RDR_WAPPND 1
# define ERR_MALLOC 12
# define ERR_FORK 1
# define ERR_PIPE 32
# define ERR_IO 5

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <stdlib.h>
# include <errno.h>

typedef struct s_redir
{
	char			mode;
	char			*filename;
	struct s_redir	*next;
}	t_redir;

typedef struct s_spl_cmd
{
	int					parse_status;
	int					rdr_in_flag;
	int					rdr_out_flag;
	int					stdin_backup;
	int					stdout_backup;
	char				*spl_cmd;
	char				*argv_line;
	char				**argv;
	char				*error_msg;
	t_redir				*rdr;
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
	char	*prompt;
	int		pipe_flag;
	t_block	*cmd_list;
}	t_msh;

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
