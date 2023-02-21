/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:38:32 by ede-smet          #+#    #+#             */
/*   Updated: 2023/02/21 20:17:19 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_STRUCT_H
# define MINI_STRUCT_H

# define EXEC_CMD 1
//# define REDIR_CMD 2
# define PIPE_CMD 3
# define LIST_CMD 4

# define STR_WHSPACE " \t\n\r\v"
# define STR_REDIR "<>"
# define STR_QUOTE "\'\""
# define STR_BRACKETS "()"
# define STR_LOL "|&"
//# define MAXARGC 10

typedef struct s_cmd
{
	int		type;
}	t_cmd;

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

typedef struct s_pipe_cmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipe;

typedef struct s_logical_list_cmd
{
	int		type;
	char	mode;
	t_cmd	*left;
	t_cmd	*right;
}	t_lol;

typedef struct s_stx
{
	char	special_ch;
	int		quo_flag;
	int		brackets_flag;
}	t_stx;

#endif
