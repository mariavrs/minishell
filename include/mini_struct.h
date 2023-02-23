/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:38:32 by ede-smet          #+#    #+#             */
/*   Updated: 2023/02/22 23:37:06 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_STRUCT_H
# define MINI_STRUCT_H

# define EXEC_CMD 1
# define PIPE_CMD 2
# define LIST_CMD 3

# define STR_WHSPACE " \t\n\r\v"
# define STR_REDIR "<>"
# define STR_QUOTE "\'\""
# define STR_BRACKETS "()"
# define STR_LOL "|&"

# include <sys/stat.h>//duplicate from mini_fun.h, reotganization of .h t be done

typedef struct s_redir
{
	char	*file;
	char	mode;
	int		fd;
}	t_redir;

typedef struct s_simple_cmd
{
	int		type;
	char	**argv;
	int		argc;
	int		redirc;
	int		stdin_cpy;
	int		stdout_cpy;
	t_redir	*redir;
}	t_spl_cmd;

typedef struct s_heredoc
{
	char		*line;
	char		*hdoc;
	char		*hdoc_id;
	struct stat	statbuf;
}	t_heredoc;

typedef struct s_stx
{
	char	special_ch;
	int		quo_flag;
	int		brackets_flag;
}	t_stx;

typedef struct s_msh
{
	char	**envp;
	char	**envp_lcl;
	char	*sline;
	int		exit_status;
}	t_msh;

typedef struct s_cmd_build
{
	int		symb_count;
	int		env_flag;
	int		quote;
	char	mode;
	char	*line;
}	t_cmd_bld;

typedef struct s_param_expan
{
	char	*str;
	struct	s_param_expan *next;
}	t_pexp;

#endif
